// Kruskal's Minimum Spanning Tree algorithm, backed by a union-find
// (disjoint-set) structure with path compression and union by rank.
//
// Reads a weighted, undirected graph as an edge list from stdin:
//   first line: V E        (number of vertices, number of edges)
//   next E lines: u v w    (edge between vertices u and v, 0-indexed, weight w)
//
// Prints:
//   - each MST edge as it is accepted, in the order Kruskal's considers it
//   - total MST weight
//   - number of edges considered / accepted / rejected
//   - number of connected components in the final forest (1 if the graph
//     is connected, i.e. a true spanning tree)
//   - wall-clock time in microseconds
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ kruskal.cpp -o kruskal
// Run:    ./kruskal < graph.txt

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>

struct Edge {
    int u, v;
    long long w;
};

// Disjoint-set union (union-find) with path compression and union by rank.
// find() flattens the tree on every call (path compression); unite() always
// attaches the shorter/lower-rank tree under the taller one (union by rank).
// Together these keep every operation close to O(1) amortized -- formally
// O(alpha(n)), where alpha is the inverse Ackermann function.
class UnionFind {
public:
    explicit UnionFind(int n) : parent(n), rank_(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        // Path compression: point every node on the path directly at the root.
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Returns false if x and y were already in the same component (union
    // was a no-op); true if they were merged.
    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return false;
        // Union by rank: attach the lower-rank root under the higher-rank one.
        if (rank_[rx] < rank_[ry]) std::swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
        return true;
    }

    int countComponents() {
        int count = 0;
        for (size_t i = 0; i < parent.size(); i++) {
            if (find(static_cast<int>(i)) == static_cast<int>(i)) count++;
        }
        return count;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank_;
};

int main() {
    int V, E;
    if (!(std::cin >> V >> E)) {
        std::cerr << "failed to read V and E\n";
        return 1;
    }

    std::vector<Edge> edges(E);
    for (int i = 0; i < E; i++) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // The core greedy step: sort all edges cheapest-first.
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    UnionFind dsu(V);
    long long totalWeight = 0;
    long long considered = 0;
    long long accepted = 0;
    long long rejected = 0;
    std::vector<Edge> mstEdges;
    mstEdges.reserve(V > 0 ? V - 1 : 0);

    for (const Edge& e : edges) {
        considered++;
        // Accept the edge unless its endpoints are already connected --
        // adding it then would only create a cycle, never help connectivity.
        if (dsu.unite(e.u, e.v)) {
            accepted++;
            totalWeight += e.w;
            mstEdges.push_back(e);
            if (accepted == V - 1) break; // full spanning tree reached early
        } else {
            rejected++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    for (const Edge& e : mstEdges) {
        std::cout << "edge: " << e.u << " " << e.v << " " << e.w << "\n";
    }
    std::cout << "total_weight=" << totalWeight << "\n";
    std::cout << "edges_considered=" << considered << "\n";
    std::cout << "edges_accepted=" << accepted << "\n";
    std::cout << "edges_rejected=" << rejected << "\n";
    std::cout << "components=" << dsu.countComponents() << "\n";
    std::cout << "microseconds=" << micros << "\n";
    return 0;
}
