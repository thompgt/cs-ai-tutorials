# Longest Common Subsequence (LCS)

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/strings); no prior algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

LCS finds the longest sequence that is a subsequence of both of two input
sequences — elements in the same relative order, not necessarily
contiguous — which is exactly what tools like `git diff` use to figure out
what actually changed between two file versions. This tutorial opens with
the "how does `git diff` know what changed" hook and a hand-traced 7/6
character example before introducing any notation, then formally states
the recurrence, proves correctness by induction, derives the $O(mn)$ time
and space complexity, and derives the backtracking procedure that
reconstructs the actual LCS string (not just its length) from the
completed table. All of this is confirmed against a **real, compiled C++
implementation** (`src/lcs.cpp`) that is actually built with `g++` and run
via `subprocess` from the notebook — the LCS length, reconstructed string,
diff-style output, and timings are real measurements, not simulated
numbers.

## Learning objectives

- Explain the difference between a subsequence and a substring, and state
  the LCS recurrence precisely.
- Prove by induction that the DP table correctly computes LCS length for
  every prefix pair, and derive the $O(mn)$ time/space bound.
- Derive the backtracking procedure that reconstructs the actual LCS
  string from a completed DP table, including how to handle ties.
- Compile and run a real C++ LCS implementation with a diff-style output
  mode, and confirm its measured runtime tracks $O(mn)$ across several
  string-length combinations.
- Know LCS's real-world tradeoffs and neighbors: why production diff tools
  use Myers' algorithm instead of raw LCS DP, why bioinformatics uses
  BLAST instead of LCS DP on whole genomes, how edit distance differs from
  LCS, and why LCS reconstruction is not unique when there are ties.

## Contents

- `tutorial.ipynb` — intro hook, intuitive walkthrough with a hand-traced
  table, formal recurrence and induction proof, visuals (DP table heatmap
  with the backtracking path overlaid, real runtime-vs-`m*n` benchmark
  plot), real compiled-C++ implementation with a diff-style output mode,
  use cases, limitations & debates
- `src/lcs.cpp` — the real C++ implementation, compiled and run from the
  notebook. Builds the full DP table, backtracks to reconstruct the LCS
  string, and produces a diff-style rendering of both inputs against the
  LCS. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/lcs.cpp -o src/lcs.exe`

## References

- Hirschberg, D.S. *A Linear Space Algorithm for Computing Maximal Common
  Subsequences*, Communications of the ACM, 1975.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapters 14/15.
- Myers, E.W. *An O(ND) Difference Algorithm and Its Variations*,
  Algorithmica, 1986.
