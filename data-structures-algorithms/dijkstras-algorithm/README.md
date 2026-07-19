# Dijkstra's Algorithm

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/lists); no prior algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

Dijkstra's algorithm finds the shortest-cost path from one source node to
every other node in a graph with non-negative edge weights, by always
"finalizing" the closest unvisited node next and relaxing its outgoing
edges. This tutorial opens with a plain-English GPS/road-trip analogy and a
hand-traced 6-node example — including an early Python snippet performing
one relaxation step on a toy adjacency structure — before introducing any
notation, then formally defines relaxation, proves the greedy-choice
correctness argument by induction, shows exactly where that proof breaks
on negative edge weights (with a concrete 3-node counterexample run
through the real compiled program to watch it fail live), and derives the
$O((V+E)\log V)$ complexity of a binary-heap-backed implementation. All of
this is confirmed against a **real, compiled C++ implementation**
(`src/dijkstra.cpp`) that is actually built with `g++` and run via
`subprocess` from the notebook — relaxation counts and timings are real
measurements, not simulated numbers.

## Learning objectives

- Explain Dijkstra's greedy "closest unvisited node next" strategy and the
  relaxation operation that updates neighbor distances.
- Prove the greedy-choice correctness argument by induction, and explain
  precisely why it depends on non-negative edge weights.
- Derive the $O((V+E)\log V)$ complexity of a binary-heap-backed
  implementation, and know the theoretically optimal $O(E+V\log V)$
  Fibonacci-heap bound as a forward reference.
- Compile and run a real C++ Dijkstra implementation, and confirm its
  measured runtime tracks the theoretical $(V+E)\log V$ curve across
  randomly generated graphs spanning three orders of magnitude.
- Know Dijkstra's real-world tradeoffs against Bellman-Ford (negative
  weights, $O(VE)$), Floyd-Warshall (all-pairs, $O(V^3)$), and a plain
  array-based $O(V^2)$ implementation (which can beat the heap-based
  version on dense graphs).

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a hand-traced
  example, formal correctness proof and complexity derivation, visuals (a
  real weighted-graph diagram and a real runtime-vs-size benchmark, both
  from the compiled program), the real compiled-C++ implementation and
  measurements, use cases, limitations & debates
- `src/dijkstra.cpp` — the real C++ implementation, compiled and run from
  the notebook. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/dijkstra.cpp -o src/dijkstra.exe`

## References

- Dijkstra, E. W. *A Note on Two Problems in Connexion with Graphs*,
  Numerische Mathematik, 1959.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 24.
- Fredman, M. L. & Tarjan, R. E. *Fibonacci Heaps and Their Uses in
  Improved Network Optimization Algorithms*, Journal of the ACM, 1987.
- `src/dijkstra.cpp`
