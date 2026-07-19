// Dijkstra's single-source shortest-path algorithm, using an adjacency list
// and a binary-heap-backed priority queue (std::priority_queue).
//
// Reads a directed, non-negatively weighted graph and a source node from
// stdin, and prints:
//   - the shortest distance from the source to every node (or "INF" if
//     unreachable)
//   - the number of relaxations performed (successful distance updates)
//   - the wall-clock time in microseconds
//
// Input format:
//   V E source
//   u1 v1 w1
//   u2 v2 w2
//   ...
//   (E lines total, one directed edge u -> v with weight w each; nodes are
//    0-indexed integers in [0, V). For an undirected road network, supply
//    both directions as two edges.)
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ dijkstra.cpp -o dijkstra
// Run:    echo "5 6 0\n0 1 4\n0 2 1\n2 1 2\n1 3 1\n2 3 5\n3 4 3" | ./dijkstra

#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <limits>

struct Edge {
    int to;
    long long weight;
};

int main() {
    int V, E, source;
    if (!(std::cin >> V >> E >> source)) {
        std::cerr << "failed to read V, E, source\n";
        return 1;
    }

    std::vector<std::vector<Edge>> adj(V);
    for (int i = 0; i < E; i++) {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    const long long INF = std::numeric_limits<long long>::max();
    std::vector<long long> dist(V, INF);
    std::vector<bool> finalized(V, false);
    long long relaxations = 0;

    // Min-heap of (distance, node), ordered by smallest distance on top.
    using DistNode = std::pair<long long, int>;
    std::priority_queue<DistNode, std::vector<DistNode>, std::greater<DistNode>> pq;

    dist[source] = 0;
    pq.push({0, source});

    auto start = std::chrono::high_resolution_clock::now();

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Stale heap entry (we already found a better one for u) -- skip.
        if (d > dist[u]) continue;
        if (finalized[u]) continue;
        finalized[u] = true; // greedy choice: u's distance is now final

        for (const Edge& e : adj[u]) {
            if (finalized[e.to]) continue;
            long long candidate = dist[u] + e.weight;
            if (candidate < dist[e.to]) {
                dist[e.to] = candidate;
                pq.push({candidate, e.to});
                relaxations++;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    for (int i = 0; i < V; i++) {
        std::cout << "dist " << i << " ";
        if (dist[i] == INF) {
            std::cout << "INF\n";
        } else {
            std::cout << dist[i] << "\n";
        }
    }
    std::cout << "relaxations=" << relaxations << "\n";
    std::cout << "microseconds=" << micros << "\n";
    return 0;
}
