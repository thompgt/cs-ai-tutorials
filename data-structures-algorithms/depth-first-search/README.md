# Depth-First Search

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, recursion, arrays/lists); no prior graph-algorithms background needed
**Language:** Java (real, compiled, and executed — see `src/`)

## Summary

Depth-first search explores a graph the way you'd explore a cave with a
ball of string: commit to the first unvisited neighbor, then its first
unvisited neighbor, plunging as deep as possible before backtracking only
when you hit a dead end. This tutorial opens with that cave/maze analogy
and an explicit contrast against breadth-first search's "check every
nearby room first" strategy, hand-traces DFS on a 7-node toy graph with
side-by-side recursive and explicit-stack Python implementations, then
goes deep on the CLRS discover/finish-time framework: the parenthesis
theorem (proved), the $O(V+E)$ time-complexity derivation, formal edge
classification (tree/back/forward/cross), and a full proof of *why* a back
edge in a directed graph always means a cycle exists — the fact that makes
DFS the standard cycle-detection algorithm.

All of this is confirmed against a **real, compiled Java implementation**
(`src/DFS.java`) that is actually built with `javac` and run via
`subprocess` from the notebook — both the recursive and explicit-stack
iterative versions are implemented from scratch, instrumented to report
discover/finish times and per-edge classification, and cross-checked
against each other on a real run. The notebook also triggers a real
`StackOverflowError` from the recursive version on a 200,000-vertex chain
graph and shows the iterative version handling the same input cleanly —
a real, not simulated, demonstration of recursive DFS's practical
limitation.

## Learning objectives

- Trace DFS by hand and predict its visit order, and explain why that
  order is exactly "stack order," whether the stack is implicit
  (recursion) or explicit (a hand-managed stack).
- State and prove the parenthesis theorem for discover/finish-time
  intervals, and use it to derive DFS's $O(V+E)$ time complexity.
- Formally classify any edge examined during DFS as tree, back, forward,
  or cross, and prove that a back edge in a directed graph exists if and
  only if the graph has a cycle.
- Compile and run a real Java DFS implementation (recursive and
  explicit-stack iterative), confirm the two variants agree exactly on
  discover/finish times and edge classification, and detect cycles via
  real back-edge output.
- Know DFS's real practical limits: recursive DFS's call-stack depth is a
  genuine crash risk on deep graphs (shown with a real
  `StackOverflowError`), and DFS does **not** guarantee shortest paths the
  way BFS does — know which traversal actually answers your question.

## Contents

- `tutorial.ipynb` — cave/maze intro contrasting DFS with BFS, intuitive
  walkthrough with side-by-side recursive/iterative Python traces, formal
  proofs (parenthesis theorem, $O(V+E)$, back-edge-implies-cycle), visuals
  (a real graph diagram colored by DFS edge classification, a real
  discover/finish timeline chart), the real compiled-Java implementation
  and measurements, use cases, and limitations & debates.
- `src/DFS.java` — the real Java implementation, compiled and run from the
  notebook. Build manually with:
  `javac src/DFS.java`
  and run with:
  `java -cp src DFS < graph.txt` (see the file's header comment for the
  stdin graph format).

## References

- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  3rd/4th ed., Chapter 22.
- Hopcroft, J. & Tarjan, R. *Efficient Algorithms for Graph Manipulation*,
  Communications of the ACM, 1973.
- Tarjan, R. *Depth-First Search and Linear Graph Algorithms*, SIAM
  Journal on Computing, 1972.
- `src/DFS.java` in this tutorial's folder — the real, compiled
  implementation used for every measurement above.
