// Floyd-Warshall all-pairs shortest path algorithm, with negative-cycle
// detection, self-timing, and (when the graph has no negative edges) a
// Dijkstra-run-V-times baseline for comparison.
//
// Input format (read from stdin):
//   V E
//   u1 v1 w1
//   u2 v2 w2
//   ...
//   (E lines total, one directed edge u -> v with weight w each; nodes are
//    0-indexed integers in [0, V). Weights may be negative. Do not include
//    a genuine negative cycle if you want a well-defined "shortest path" --
//    the program will still run and will report one if it finds it.)
//
// Output:
//   - the full VxV distance matrix after running Floyd-Warshall ("INF" for
//     unreachable pairs)
//   - "negative_cycle=yes"/"no", and if yes, one node index i with
//     dist[i][i] < 0 as a witness
//   - "fw_microseconds=<time>" for the Floyd-Warshall run
//   - if (and only if) the input graph has no negative edge weights, also:
//       - the VxV distance matrix from running Dijkstra V times (once per
//         source), for direct comparison
//       - "dijkstra_microseconds=<time>"
//       - "agree=yes"/"no" -- whether the two matrices match exactly
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ floyd_warshall.cpp -o floyd_warshall
// Run:    echo "4 5\n0 1 3\n0 2 8\n1 3 1\n2 1 -4\n3 2 2" | ./floyd_warshall

#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <limits>

static const long long INF = std::numeric_limits<long long>::max() / 4; // avoid overflow when summing

// Runs Floyd-Warshall in place on `dist` (VxV). Returns true if a negative
// cycle is detected (dist[i][i] < 0 for some i after relaxation).
bool floydWarshall(std::vector<std::vector<long long>>& dist, int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            if (dist[i][k] >= INF) continue; // no path i -> k, skip (avoids overflow too)
            for (int j = 0; j < V; j++) {
                if (dist[k][j] >= INF) continue;
                long long candidate = dist[i][k] + dist[k][j];
                if (candidate < dist[i][j]) {
                    dist[i][j] = candidate;
                }
            }
        }
    }
    bool negativeCycle = false;
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) negativeCycle = true;
    }
    return negativeCycle;
}

struct Edge {
    int to;
    long long weight;
};

// Single-source Dijkstra (non-negative weights only), returns distance vector.
std::vector<long long> dijkstra(const std::vector<std::vector<Edge>>& adj, int V, int source) {
    std::vector<long long> dist(V, INF);
    std::vector<bool> finalized(V, false);
    using DistNode = std::pair<long long, int>;
    std::priority_queue<DistNode, std::vector<DistNode>, std::greater<DistNode>> pq;

    dist[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        if (finalized[u]) continue;
        finalized[u] = true;
        for (const Edge& e : adj[u]) {
            if (finalized[e.to]) continue;
            long long candidate = dist[u] + e.weight;
            if (candidate < dist[e.to]) {
                dist[e.to] = candidate;
                pq.push({candidate, e.to});
            }
        }
    }
    return dist;
}

int main() {
    int V, E;
    if (!(std::cin >> V >> E)) {
        std::cerr << "failed to read V, E\n";
        return 1;
    }

    std::vector<std::vector<long long>> dist(V, std::vector<long long>(V, INF));
    std::vector<std::vector<Edge>> adj(V);
    for (int i = 0; i < V; i++) dist[i][i] = 0;

    bool hasNegativeEdge = false;
    for (int e = 0; e < E; e++) {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        if (w < dist[u][v]) dist[u][v] = w; // keep cheapest of parallel edges
        adj[u].push_back({v, w});
        if (w < 0) hasNegativeEdge = true;
    }

    auto fwStart = std::chrono::high_resolution_clock::now();
    bool negativeCycle = floydWarshall(dist, V);
    auto fwEnd = std::chrono::high_resolution_clock::now();
    auto fwMicros = std::chrono::duration_cast<std::chrono::microseconds>(fwEnd - fwStart).count();

    std::cout << "V=" << V << "\n";
    std::cout << "matrix_fw:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] >= INF) {
                std::cout << "INF";
            } else {
                std::cout << dist[i][j];
            }
            std::cout << (j + 1 < V ? " " : "\n");
        }
    }

    int witness = -1;
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) { witness = i; break; }
    }
    std::cout << "negative_cycle=" << (negativeCycle ? "yes" : "no") << "\n";
    if (negativeCycle) {
        std::cout << "negative_cycle_witness=" << witness << "\n";
    }
    std::cout << "fw_microseconds=" << fwMicros << "\n";

    // Only meaningful to compare against Dijkstra when there are no negative
    // edges at all (Dijkstra's greedy finalization is unsound otherwise).
    if (!hasNegativeEdge) {
        std::vector<std::vector<long long>> dijkstraDist(V, std::vector<long long>(V, INF));
        auto dijkstraStart = std::chrono::high_resolution_clock::now();
        for (int s = 0; s < V; s++) {
            dijkstraDist[s] = dijkstra(adj, V, s);
        }
        auto dijkstraEnd = std::chrono::high_resolution_clock::now();
        auto dijkstraMicros = std::chrono::duration_cast<std::chrono::microseconds>(dijkstraEnd - dijkstraStart).count();

        std::cout << "matrix_dijkstra:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dijkstraDist[i][j] >= INF) {
                    std::cout << "INF";
                } else {
                    std::cout << dijkstraDist[i][j];
                }
                std::cout << (j + 1 < V ? " " : "\n");
            }
        }

        bool agree = true;
        for (int i = 0; i < V && agree; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] != dijkstraDist[i][j]) { agree = false; break; }
            }
        }
        std::cout << "dijkstra_microseconds=" << dijkstraMicros << "\n";
        std::cout << "agree=" << (agree ? "yes" : "no") << "\n";
    }

    return 0;
}
