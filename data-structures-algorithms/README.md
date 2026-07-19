# Data Structures & Algorithms

Core CS: arrays, trees, graphs, hash tables, sorting/searching, and complexity analysis.

## Tutorials

| Tutorial | Language | What it covers |
|---|---|---|
| [Quicksort](quicksort) | C++ | In-place divide-and-conquer sorting via partitioning; correctness proof, average/worst-case analysis, and why randomized pivoting matters |
| [Merge Sort](merge-sort) | C++ | Guaranteed Θ(n log n) divide-and-conquer sorting; stability proof, and the space-vs-guarantee tradeoff against quicksort |
| [Binary Search](binary-search) | C++ | Θ(log n) search via loop-invariant halving; lower_bound/upper_bound variants and the classic overflow bug |
| [Binary Search Tree](binary-search-tree) | Java | Insert/search/delete with in-order traversal; O(h) complexity and why unbalanced BSTs degenerate to O(n) |
| [AVL Tree](avl-tree) | Java | Self-balancing BST via rotations; balance-factor invariant and the O(log n) height guarantee |
| [Trie](trie) | Java | Prefix tree for O(L) insert/search/prefix-query; autocomplete and IP-routing use cases |
| [Binary Heap / Priority Queue](binary-heap) | Java | Array-backed min-heap; O(log n) insert/extract-min and the O(n) heapify derivation |
| [Breadth-First Search](breadth-first-search) | Java | Shortest paths in unweighted graphs via FIFO traversal; O(V+E) and the distance-layer proof |
| [Depth-First Search](depth-first-search) | Java | Recursive/iterative graph traversal; discover/finish times, edge classification, and cycle detection |
| [Dijkstra's Algorithm](dijkstras-algorithm) | C++ | Single-source shortest paths with non-negative weights; greedy correctness proof and why negative edges break it |
| [A* Search](a-star-search) | C++ | Heuristic-guided pathfinding; admissibility, and why A* with h=0 is exactly Dijkstra |
| [Union-Find](union-find) | C++ | Disjoint-set structure with union-by-rank and path compression; the amortized inverse-Ackermann bound |
| [Kruskal's MST](kruskals-mst) | C++ | Minimum spanning trees via greedy edge selection and union-find; the cut-property correctness proof |
| [Topological Sort](topological-sort) | Java | Dependency ordering on DAGs via Kahn's algorithm and DFS finish-time order; cycle detection |
| [0/1 Knapsack](01-knapsack) | C++ | Dynamic programming for constrained selection; the pseudo-polynomial complexity distinction |
| [Longest Common Subsequence](longest-common-subsequence) | C++ | DP string comparison with backtracking reconstruction; the diff/bioinformatics connection |
| [Floyd-Warshall](floyd-warshall) | C++ | All-pairs shortest paths via DP; negative-cycle detection and the Θ(V³) bound |
| [Huffman Coding](huffman-coding) | Java | Optimal prefix-free compression via greedy tree merging; the exchange-argument optimality proof |
| [KMP String Matching](kmp-string-matching) | C++ | Linear-time exact string search via the failure function; why the text pointer never backtracks |

See [CONTRIBUTING.md](../CONTRIBUTING.md) to add another.
