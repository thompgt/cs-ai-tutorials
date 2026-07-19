# Kruskal's Minimum Spanning Tree Algorithm

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/lists); no prior graph
algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

Kruskal's algorithm builds the cheapest possible network connecting a set of
locations by sorting every candidate edge by cost and greedily accepting
each one unless it would close a redundant loop with edges already
accepted. This tutorial opens with a plain-English "telecom company laying
minimum-cost cable" analogy and a hand-traced 7-town example before
introducing any notation, then formally states the **cut property** of
minimum spanning trees and uses it to prove why the greedy choice is always
safe, and derives the $O(E \log E)$ overall complexity (edge sort dominates;
union-find operations are near-linear, $O(E \cdot \alpha(V))$). All of this
is confirmed against a **real, compiled C++ implementation**
(`src/kruskal.cpp`) — including a from-scratch **union-find (disjoint-set)**
structure with path compression and union by rank — that is actually built
with `g++` and run via `subprocess` from the notebook: MST edges, total
weight, edge-acceptance stats, and timing are real measurements, not
simulated numbers.

## Learning objectives

- Explain Kruskal's greedy edge-acceptance rule and why it always produces
  a spanning tree with no redundant edges.
- State the cut property of minimum spanning trees and use it to prove
  Kruskal's correctness — not just observe that it works.
- Derive the $O(E \log E)$ overall running time, and explain why
  union-find with path compression and union by rank keeps the
  connectivity checks themselves near-linear, $O(E \cdot \alpha(V))$.
- Compile and run a real C++ Kruskal's implementation, watch the forest
  grow step by step on a small graph, and confirm measured runtime tracks
  $E \log_2 E$ across growing real graphs.
- Know Kruskal's real-world tradeoffs against Prim's algorithm (edge-sort
  vs. heap-based growth, sparse vs. dense graphs) and where MST shows up in
  practice (network design, circuit design, TSP approximation, clustering).

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a
  hand-traced example, formal cut-property proof and complexity
  derivation, visuals (forest-growth snapshots, real original-vs-MST graph
  diagram, real runtime benchmark plot), real compiled-C++ implementation
  and measurements, use cases, limitations & debates
- `src/kruskal.cpp` — the real C++ implementation (edge sort + from-scratch
  union-find with path compression and union by rank), compiled and run
  from the notebook. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/kruskal.cpp -o src/kruskal.exe`

## References

- Kruskal, J. B. *On the Shortest Spanning Subtree of a Graph and the
  Traveling Salesman Problem*, Proceedings of the American Mathematical
  Society, 1956.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 23.
- `src/kruskal.cpp` — the real, compiled implementation used for every
  measurement in the notebook.
