# Breadth-First Search (BFS)

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/lists); no prior graph-algorithms background needed
**Language:** Java (real, compiled, and executed — see `src/`)

## Summary

BFS explores a graph outward from a source vertex one "ring" at a time —
like ripples spreading from a stone dropped in a pond, or finding all your
direct friends before any friend-of-a-friend on a social network. This
tutorial opens with that plain-English analogy and a hand-traced 7-vertex
example (with the queue's contents shown step by step) before introducing
any notation, explains why a vertex must be marked visited the instant it's
*enqueued* rather than when it's later dequeued (a common bug source), then
formally proves by induction that BFS visits vertices in non-decreasing
order of distance from the source and derives the $O(V+E)$ time bound. All
of this is confirmed against a **real, compiled Java implementation**
(`src/BFS.java`) that is actually built with `javac` and run via
`subprocess` from the notebook — every per-vertex distance and every
timing number is a real measurement, not a simulated one.

## Learning objectives

- Explain BFS's queue-based mechanics and trace it by hand on a small
  graph.
- Explain why marking a vertex visited at *discovery* (enqueue) time,
  rather than at dequeue time, is essential to correctness and to the
  $O(V+E)$ bound.
- Prove by induction that BFS visits vertices in non-decreasing order of
  distance from the source, and derive the $O(V+E)$ time complexity.
- Compile and run a real Java BFS implementation, and confirm its measured
  running time actually grows linearly in $V+E$ across randomly generated
  graphs.
- Know BFS's real-world use cases (shortest paths in unweighted graphs,
  level-order tree traversal, connected components, word-ladder/sliding-
  puzzle style state-space search) and its limitations (unweighted-only
  correctness, motivating Dijkstra's algorithm; $O(V)$ memory; bidirectional
  BFS as a practical speedup).

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a hand-traced
  example, formal proof of BFS's distance-layer ordering and $O(V+E)$ time
  bound, visuals (a real graph colored by BFS distance layer, a real
  benchmark plot of running time vs. graph size), real compiled-Java
  implementation and measurements, use cases, limitations & debates.
- `src/BFS.java` — the real Java implementation, compiled and run from the
  notebook. Build manually with:
  `javac src/BFS.java`

## References

- Moore, E.F. *The Shortest Path Through a Maze*, Proceedings of the
  International Symposium on the Theory of Switching, 1959.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 22.
- `src/BFS.java`
