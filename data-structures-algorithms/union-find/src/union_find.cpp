// Union-Find / Disjoint Set Union (DSU), three variants for comparison:
//   1. naive        -- plain union, no optimization at all
//   2. rank         -- union by rank only (attach the shorter tree under the taller)
//   3. rank_pc      -- union by rank + path compression during find()
//
// All three variants are run, independently, on the *same* sequence of
// operations read from stdin, so their behavior can be compared head to
// head on identical input.
//
// Input format (whitespace-separated):
//   n                    -- number of elements, labeled 0..n-1
//   q                    -- number of operations
//   then q operation lines, each one of:
//     U a b              -- union(a, b)
//     F a                -- find(a); counts toward the "pure find" hop
//                           statistics used for the path-length benchmark
//     Q a b              -- same-set query: is a connected to b? (also
//                           calls find twice, but is tracked separately
//                           as a "query" rather than a benchmark find)
//
// For each variant, stdout gets a block:
//   ===VARIANT <name>
//   microseconds=<total wall-clock time processing all ops>
//   total_hops=<pointer hops across ALL find calls, from any op type>
//   find_op_count=<number of 'F' ops processed>
//   find_op_hops=<pointer hops incurred by 'F' ops only>
//   components=<number of disjoint sets remaining>
//   query_results=<comma-separated 0/1, one per 'Q' op, in order>
//   parents=<comma-separated parent[i] for i=0..n-1, final internal state>
//   ===END
//
// A "hop" is one step of following a parent pointer during find()'s
// upward walk to the root -- it does NOT include the second-pass writes
// that path compression performs, so find_op_hops measures the same
// thing (traversal cost to the root) across all three variants fairly.
//
// Build:  g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ union_find.cpp -o union_find
// Run:    echo "4\n3\nU 0 1\nU 1 2\nQ 0 2" | ./union_find

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

// ---------------------------------------------------------------------
// Variant 1: naive union-find. No union-by-rank, no path compression.
// union(x, y) always grafts root(x) under root(y). On a sequential chain
// of unions (0,1), (1,2), (2,3), ... this produces a straight-line chain
// of length n -- find() on the far end costs O(n) pointer hops.
// ---------------------------------------------------------------------
struct NaiveDSU {
    std::vector<int> parent;
    long long totalHops = 0;

    explicit NaiveDSU(int n) : parent(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x, long long& hopCounter) {
        int hops = 0;
        while (parent[x] != x) {
            x = parent[x];
            hops++;
        }
        hopCounter += hops;
        totalHops += hops;
        return x;
    }

    void unite(int a, int b, long long& hopCounter) {
        int ra = find(a, hopCounter);
        int rb = find(b, hopCounter);
        if (ra == rb) return;
        parent[ra] = rb; // no size/rank guidance -- can build a long chain
    }
};

// ---------------------------------------------------------------------
// Variant 2: union by rank only, no path compression. Always attaches
// the shorter (lower-rank) tree under the taller tree's root, which
// keeps every tree's height at O(log n) -- but find() still walks the
// full path every time since nothing gets compressed.
// ---------------------------------------------------------------------
struct RankDSU {
    std::vector<int> parent;
    std::vector<int> rank_;
    long long totalHops = 0;

    explicit RankDSU(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x, long long& hopCounter) {
        int hops = 0;
        while (parent[x] != x) {
            x = parent[x];
            hops++;
        }
        hopCounter += hops;
        totalHops += hops;
        return x;
    }

    void unite(int a, int b, long long& hopCounter) {
        int ra = find(a, hopCounter);
        int rb = find(b, hopCounter);
        if (ra == rb) return;
        if (rank_[ra] < rank_[rb]) std::swap(ra, rb);
        parent[rb] = ra; // attach the shorter/equal tree under the taller
        if (rank_[ra] == rank_[rb]) rank_[ra]++;
    }
};

// ---------------------------------------------------------------------
// Variant 3: union by rank + path compression. Same union rule as
// RankDSU, but find() does a second pass that re-points every node it
// visited directly at the root, so the *next* find on any of those
// nodes is O(1). This is the combination that gives the amortized
// O(alpha(n)) bound.
// ---------------------------------------------------------------------
struct RankPathCompressionDSU {
    std::vector<int> parent;
    std::vector<int> rank_;
    long long totalHops = 0;

    explicit RankPathCompressionDSU(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x, long long& hopCounter) {
        // Pass 1: walk to the root, counting hops (same cost model as
        // the other two variants -- compression happens *after*).
        int root = x;
        int hops = 0;
        while (parent[root] != root) {
            root = parent[root];
            hops++;
        }
        hopCounter += hops;
        totalHops += hops;

        // Pass 2: path compression -- re-point every node on the path
        // directly at the root.
        while (parent[x] != root) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        return root;
    }

    void unite(int a, int b, long long& hopCounter) {
        int ra = find(a, hopCounter);
        int rb = find(b, hopCounter);
        if (ra == rb) return;
        if (rank_[ra] < rank_[rb]) std::swap(ra, rb);
        parent[rb] = ra;
        if (rank_[ra] == rank_[rb]) rank_[ra]++;
    }
};

struct Op {
    char type; // 'U', 'F', or 'Q'
    int a, b;  // b unused for 'F'
};

template <typename DSU>
void runVariant(const std::string& name, int n, const std::vector<Op>& ops) {
    DSU dsu(n);
    long long findOpHops = 0;
    long long findOpCount = 0;
    std::vector<int> queryResults;
    long long dummyHops = 0; // for U/Q ops, hops still tracked in dsu.totalHops

    auto start = std::chrono::high_resolution_clock::now();
    for (const Op& op : ops) {
        if (op.type == 'U') {
            dsu.unite(op.a, op.b, dummyHops);
        } else if (op.type == 'F') {
            long long hc = 0;
            dsu.find(op.a, hc);
            findOpHops += hc;
            findOpCount++;
        } else if (op.type == 'Q') {
            long long hc = 0;
            int ra = dsu.find(op.a, hc);
            int rb = dsu.find(op.b, hc);
            queryResults.push_back(ra == rb ? 1 : 0);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    int components = 0;
    for (int i = 0; i < n; i++) {
        if (dsu.parent[i] == i) components++;
    }

    std::cout << "===VARIANT " << name << "\n";
    std::cout << "microseconds=" << micros << "\n";
    std::cout << "total_hops=" << dsu.totalHops << "\n";
    std::cout << "find_op_count=" << findOpCount << "\n";
    std::cout << "find_op_hops=" << findOpHops << "\n";
    std::cout << "components=" << components << "\n";

    std::cout << "query_results=";
    for (size_t i = 0; i < queryResults.size(); i++) {
        std::cout << queryResults[i] << (i + 1 < queryResults.size() ? "," : "");
    }
    std::cout << "\n";

    std::cout << "parents=";
    for (int i = 0; i < n; i++) {
        std::cout << dsu.parent[i] << (i + 1 < n ? "," : "");
    }
    std::cout << "\n";
    std::cout << "===END\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<Op> ops;
    ops.reserve(q);
    for (int i = 0; i < q; i++) {
        std::string type;
        std::cin >> type;
        Op op{};
        op.type = type[0];
        if (op.type == 'U' || op.type == 'Q') {
            std::cin >> op.a >> op.b;
        } else { // 'F'
            std::cin >> op.a;
            op.b = -1;
        }
        ops.push_back(op);
    }

    runVariant<NaiveDSU>("naive", n, ops);
    runVariant<RankDSU>("rank", n, ops);
    runVariant<RankPathCompressionDSU>("rank_pc", n, ops);

    return 0;
}
