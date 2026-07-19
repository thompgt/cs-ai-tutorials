# Topological Sort

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/maps); comfort with graphs helps but isn't required
**Language:** Java (real, compiled, and executed — see `src/`)

## Summary

Topological sort takes a set of tasks with "this must happen before that"
dependency rules — modeled as a directed graph where edge A &rarr; B means
"A must happen before B" — and produces a linear order that respects every
rule. This tutorial opens with a plain-English course-prerequisite and
getting-dressed analogy and a hand-traced 6-node example before any
notation, then covers **both classic algorithms** (Kahn's in-degree-removal
algorithm and the DFS-based reverse-finishing-time method), formally proves
a valid order exists if and only if the graph has no cycle, derives the
$O(V+E)$ complexity of both methods, and proves why reverse-finish-time
order works via the discover/finish-time framework. All of this is
confirmed against a **real, compiled Java implementation**
(`src/TopologicalSort.java`) that is actually built with `javac` and run
via `subprocess` from the notebook — including explicit cycle detection,
real timings, and two real runs with different tie-breaking that produce
two different (both valid) topological orders on the same graph.

## Learning objectives

- Explain what a topological order is and why it generally isn't unique.
- Trace Kahn's algorithm (in-degree removal) and the DFS-based method
  (reverse finishing-time order) by hand on a small DAG.
- Prove that a topological order exists if and only if the graph is
  acyclic, and prove why reversed DFS finish-time order is always valid.
- Derive the $O(V+E)$ running time of both methods.
- Compile and run a real Java implementation with explicit cycle
  detection, and confirm its measured timings track the theoretical
  linear-in-graph-size bound.
- Know topological sort's real-world tradeoffs: why undetected cycles are
  a genuine class of production bug (build systems, package managers,
  spreadsheet circular references), and why code that depends on a
  *specific* valid order rather than *any* valid order is fragile.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a
  hand-traced example, formal proofs (existence iff acyclic,
  discover/finish-time correctness proof), visuals (a real DAG diagram
  showing two different valid orders side by side, a real benchmark
  plot), real compiled-Java implementation and measurements, use cases,
  limitations & debates
- `src/TopologicalSort.java` — the real Java implementation (Kahn's
  algorithm and the DFS-based method, both with cycle detection and
  self-timing), compiled and run from the notebook. Build manually with:
  `javac src/TopologicalSort.java`

## References

- Kahn, A. B. *Topological Sorting of Large Networks*, Communications of
  the ACM, 1962 (the original algorithm).
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 22 (DFS-based topological sort and its correctness proof).
- `src/TopologicalSort.java` in this tutorial's folder — the real,
  compiled implementation used for every measurement above.
