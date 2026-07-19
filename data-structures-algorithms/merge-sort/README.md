# Merge Sort

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/lists); no prior algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

Merge sort sorts by splitting an array exactly in half, recursing down to
single elements, then merging sorted halves back together with a
two-pointer scan. This tutorial opens with a plain-English "two graders
combining their sorted exam piles" analogy and a hand-traced 8-element
split-then-merge example before introducing any notation, then formally
proves the merge step's correctness via a loop invariant, proves merge
sort's stability from the merge's tie-breaking rule, and derives the
recurrence $T(n) = 2T(n/2) + \Theta(n)$ via the Master Theorem to get a
**guaranteed** (not average-case) $\Theta(n \log n)$ bound. All of this is
confirmed against a **real, compiled C++ implementation**
(`src/merge_sort.cpp`) that is actually built with `g++` and run via
`subprocess` from the notebook — comparison counts, move counts, and
timing are real measurements, not simulated numbers. The benchmark
honestly reports that shuffled input takes ~1.6–1.7x more comparisons than
sorted input (not "identical" as a naive intuition might suggest), while
showing that ratio stays bounded and never diverges the way quicksort's
sorted-input worst case does.

## Learning objectives

- Explain merge sort's split-then-merge structure and why the split point
  never depends on the data.
- Prove the merge step's correctness via a two-pointer loop invariant, and
  prove merge sort is stable from the merge's `<=` tie-breaking rule.
- Derive the $\Theta(n \log n)$ recurrence via the Master Theorem and
  explain why it's a worst-case guarantee, not an average-case bound —
  contrasting directly with quicksort's expected-case bound.
- Compile and run a real C++ merge sort implementation, and confirm its
  measured comparison counts track $n \log_2 n$ across shuffled, sorted,
  and reverse-sorted inputs, while honestly characterizing the real
  (bounded, non-diverging) gap between them.
- Know merge sort's real-world tradeoffs against quicksort (stability,
  worst-case guarantees, $O(n)$ auxiliary space) and where each is
  actually used (external sorting, Timsort, linked-list sorting).

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough, formal proofs
  (merge correctness, stability, recurrence/Master Theorem), visuals
  (level-by-level merge recursion plot, real benchmark plot), real
  compiled-C++ implementation and measurements, use cases, limitations &
  debates
- `src/merge_sort.cpp` — the real C++ implementation, compiled and run
  from the notebook. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/merge_sort.cpp -o src/merge_sort.exe`

## References

- Knuth, D. E. *The Art of Computer Programming, Volume 3: Sorting and
  Searching*, 2nd ed.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 2.
- von Neumann, J. *First Draft of a Report on the EDVAC*, 1945 (original
  description of merge sort).
- [cppreference: std::stable_sort](https://en.cppreference.com/w/cpp/algorithm/stable_sort)
- `src/merge_sort.cpp` in this tutorial's folder.
