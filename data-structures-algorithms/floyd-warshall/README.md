# Floyd-Warshall

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/2D matrices); no prior
algorithms background needed. Helpful (not required) to have seen a
single-source shortest-path method like Dijkstra's algorithm first, since
this tutorial explicitly contrasts against it.
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

Floyd-Warshall computes the shortest path between **every pair** of
vertices in a weighted directed graph, using a strikingly simple idea:
maintain a full distance matrix, and for each vertex `k` in turn, check
every pair `(i, j)` and ask "would routing through `k` be cheaper?" This
tutorial opens with a plain-English "airline office network" analogy and a
hand-traced 4-city example (with a single concrete relaxation check) before
introducing any notation, then formally states the `dist_k[i][j]`
recurrence, proves correctness by induction on `k`, derives the
$\Theta(V^3)$ time / $\Theta(V^2)$ space bounds, and covers negative edge
weights and negative-cycle detection precisely (`dist[i][i] < 0` after the
algorithm runs). All of this is confirmed against a **real, compiled C++
implementation** (`src/floyd_warshall.cpp`) that is actually built with
`g++` and run via `subprocess` from the notebook — the distance-matrix
heatmap, the runtime-vs-`V` benchmark, the negative-cycle demonstration,
and the agreement check against `V` repeated runs of Dijkstra are all real
measurements from the compiled binary, not simulated numbers.

## Learning objectives

- Explain Floyd-Warshall's "does routing through k help?" relaxation step
  and how it fills in an all-pairs distance matrix.
- Contrast all-pairs shortest paths (Floyd-Warshall) against single-source
  shortest paths (Dijkstra), and know when each is the right tool.
- Prove correctness by induction on the set of allowed intermediate
  vertices, and derive the $\Theta(V^3)$ time / $\Theta(V^2)$ space bounds.
- State precisely why Floyd-Warshall tolerates negative edge weights where
  Dijkstra can't, and how to detect a negative cycle
  (`dist[i][i] < 0` on the diagonal after running the algorithm).
- Compile and run a real C++ implementation, confirm its measured runtime
  tracks the theoretical $V^3$ growth (via a log-log exponent fit), and
  confirm it agrees exactly with `V` repeated runs of Dijkstra on
  non-negative graphs.
- Know Floyd-Warshall's real-world tradeoffs against Johnson's algorithm
  for sparse graphs, and why "simple $O(V^3)$" is still the right choice
  for small/dense graphs despite the worse asymptotic complexity.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a hand-traced
  example, formal recurrence and induction proof, visuals (real distance-
  matrix heatmap before/after, real runtime-vs-`V` benchmark with a log-log
  cubic fit), real compiled-C++ implementation and measurements, use cases,
  limitations & debates
- `src/floyd_warshall.cpp` — the real C++ implementation, compiled and run
  from the notebook. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/floyd_warshall.cpp -o src/floyd_warshall.exe`

## References

- Floyd, R. W. *Algorithm 97: Shortest Path*, Communications of the ACM,
  1962.
- Warshall, S. *A Theorem on Boolean Matrices*, Journal of the ACM, 1962.
- Roy, B. *Transitivité et connexité*, Comptes Rendus de l'Académie des
  Sciences, 1959.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 25.
- Johnson, D. B. *Efficient Algorithms for Shortest Paths in Sparse
  Networks*, Journal of the ACM, 1977.
