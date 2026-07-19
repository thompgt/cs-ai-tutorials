# Quicksort

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/lists); no prior algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

Quicksort sorts by picking a pivot, partitioning the array around it in one
linear pass so the pivot lands in its final sorted position, then recursing
on the two smaller pieces. This tutorial opens with a plain-English
"librarian sorting a book cart" analogy and a hand-traced 7-element example
before introducing any notation, then formally proves the partition
invariant and correctness by induction, derives the $\Theta(n \log n)$
average-case and $\Theta(n^2)$ worst-case recurrences, and explains why
randomized pivot selection defeats adversarial worst-case inputs. All of
this is confirmed against a **real, compiled C++ implementation**
(`src/quicksort.cpp`) that is actually built with `g++` and run via
`subprocess` from the notebook — comparison counts, swap counts, and timing
are real measurements, not simulated numbers.

## Learning objectives

- Explain quicksort's partition step and why it places the pivot in its
  final sorted position in one linear pass.
- Prove correctness by induction using the partition loop invariant.
- Derive the $\Theta(n \log n)$ average-case and $\Theta(n^2)$ worst-case
  recurrences, and explain why randomized pivoting gives an $O(n\log n)$
  expected bound on *any* input.
- Compile and run a real C++ quicksort implementation, and confirm its
  measured comparison counts track the theoretical $n \log_2 n$ curve
  across shuffled, sorted, and reverse-sorted inputs.
- Know quicksort's real-world tradeoffs against mergesort (stability, worst
  case guarantees, auxiliary space) and where each is actually used
  (introsort in `std::sort`, Java's dual-pivot quicksort, quickselect).

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough, formal proofs,
  visuals (recursion-depth histograms, real benchmark plot), real
  compiled-C++ implementation and measurements, use cases, limitations &
  debates
- `src/quicksort.cpp` — the real C++ implementation, compiled and run from
  the notebook. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/quicksort.cpp -o src/quicksort.exe`

## References

- Hoare, C.A.R. *Quicksort*, The Computer Journal, 1962.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 7.
- Sedgewick, R. *Implementing Quicksort Programs*, CACM, 1978.
- Musser, D. R. *Introspective Sorting and Selection Algorithms*, 1997.
- [cppreference: std::sort](https://en.cppreference.com/w/cpp/algorithm/sort)
