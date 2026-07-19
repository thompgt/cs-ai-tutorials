# 0/1 Knapsack

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/lists); no prior algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

0/1 Knapsack asks: given items each with a weight and a value, and a
capacity you can't exceed, which subset of items (each fully in or fully
out — no fractions) maximizes total value? This tutorial opens with a
plain-English "packing a backpack for a hike" analogy, explains why
brute-force checking all $2^n$ subsets is hopeless past ~30 items, and
hand-traces a tiny 4-item dynamic-programming table cell by cell before
introducing any notation. It then formally states the DP recurrence,
proves its correctness by induction, derives the $O(nW)$ time/space bound,
and carefully derives *why* that bound is called **pseudo-polynomial**
rather than polynomial — a genuinely subtle complexity-theory point that's
directly relevant to knapsack's NP-completeness, not just asserted. All of
this is confirmed against a **real, compiled C++ implementation**
(`src/knapsack.cpp`) — a full 2D DP table, a space-optimized 1D rolling
array, and a brute-force $2^n$ cross-check — actually built with `g++` and
run via `subprocess` from the notebook. Every table, plot, and timing is a
real measurement, including an empirical demonstration of the
pseudo-polynomial blow-up: runtime grows ~19,000x while the number of bits
needed to encode the capacity grows by only 14.

## Learning objectives

- Explain why brute-force enumeration of all $2^n$ subsets is infeasible
  even at modest $n$, and how the DP table `dp[i][w]` avoids recomputing
  overlapping subproblems.
- State the knapsack recurrence precisely and prove its correctness by
  induction on the number of items considered.
- Derive the $O(nW)$ time/space bound and explain — with a derivation, not
  just an assertion — why it's *pseudo-polynomial* (polynomial in $W$'s
  numeric value, exponential in the number of bits needed to encode $W$),
  and why that doesn't contradict knapsack's NP-completeness.
- Apply the $O(W)$ space optimization (1D rolling array) and explain why
  iterating capacity in reverse is required for 0/1 correctness.
- Compile and run a real C++ implementation, confirm the DP's answers
  exactly match brute force on small cases, and observe the pseudo-
  polynomial runtime blow-up in real measured timings.
- Know the fractional-knapsack variant is a different, easier,
  greedy-solvable problem, and know knapsack's practical alternative for
  huge instances (FPTAS) exists without needing to derive it in full.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a hand-traced
  DP table, formal recurrence/proof/complexity derivation, visuals (DP-table
  heatmap with backtracked path, real runtime-vs-$n \times W$ benchmark, and
  an empirical pseudo-polynomial blow-up demo), real compiled-C++
  implementation with a brute-force correctness cross-check, use cases, and
  limitations & debates
- `src/knapsack.cpp` — the real C++ implementation (full 2D DP,
  space-optimized 1D DP, and brute force), compiled and run from the
  notebook. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/knapsack.cpp -o src/knapsack.exe`

## References

- Bellman, R. *Dynamic Programming*, Princeton University Press, 1957.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 15 (Dynamic Programming) and Chapter 34 (NP-Completeness).
- Garey, M. R. & Johnson, D. S. *Computers and Intractability: A Guide to
  the Theory of NP-Completeness*, W. H. Freeman, 1979.
- `src/knapsack.cpp` in this tutorial's folder.
