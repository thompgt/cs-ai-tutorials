# Union-Find (Disjoint Set Union)

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays); no prior algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

Union-Find (Disjoint Set Union / DSU) maintains a collection of disjoint
sets under two operations — `find(x)` (which set is `x` in?) and
`union(x, y)` (merge the sets containing `x` and `y`) — using nothing but
a parent pointer per element. This tutorial opens with a plain-English
"who's in whose friend group at this party" analogy and a hand-traced
7-person example before any notation, then formally introduces the naive
version's $O(n)$ worst-case degenerate chain, the two classic
optimizations (**union by rank** and **path compression**), and the
famous **amortized $O(m\,\alpha(n))$** bound (Tarjan, 1975) — explaining
"amortized" and the **inverse Ackermann function** $\alpha(n)$ in plain
terms alongside the formal statement, with a proof-intuition sketch rather
than the full potential-function proof. All of this is confirmed against
a **real, compiled C++ implementation** (`src/union_find.cpp`) implementing
three variants side by side — naive, union-by-rank only, and union-by-rank
+ path compression — actually built with `g++` and run via `subprocess`
from the notebook: the before/after tree diagrams and the average
find-path-length benchmark are real measurements from the compiled
program's internal state, not simulated numbers.

## Learning objectives

- Explain how union-find represents groups as parent-pointer trees, and
  why `find(x) == find(y)` answers "same set?" without ever storing
  membership lists.
- Derive why the naive version's worst case is $\Theta(n)$ per `find()`
  (a degenerate long chain), and prove that union by rank alone bounds
  tree height at $O(\log n)$.
- State the amortized $O(m\,\alpha(n))$ bound for union by rank + path
  compression, explain what "amortized" and "inverse Ackermann function"
  mean in plain terms, and sketch (not fully reproduce) Tarjan's proof
  intuition.
- Compile and run a real C++ implementation of all three variants, and
  confirm from real measurements that the naive variant's average
  `find()` path length grows sharply with $n$ while both optimized
  variants stay close to flat.
- Know union-find's real-world uses (Kruskal's MST, cycle detection,
  dynamic connectivity, connected-component labeling) and its structural
  limitations — it cannot list a set's members or split a set apart, and
  "$O(\alpha(n))$" is not literally "$O(1)$."

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a toy
  Python trace, formal definitions and proofs, visuals (a real
  before/after path-compression tree diagram and a real average-find-
  path-length benchmark plot), real compiled-C++ implementation and
  measurements, use cases, limitations & debates
- `src/union_find.cpp` — the real C++ implementation (naive, rank-only,
  and rank + path-compression variants), compiled and run from the
  notebook. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/union_find.cpp -o src/union_find.exe`

## References

- Tarjan, R.E. *Efficiency of a Good But Not Linear Set Union Algorithm*,
  Journal of the ACM 22(2), 1975.
- Galler, B.A. & Fischer, M.J. *An Improved Equivalence Algorithm*,
  Communications of the ACM 7(5), 1964.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 21.
- `src/union_find.cpp` — the real, compiled implementation used for every
  measurement in the notebook.
