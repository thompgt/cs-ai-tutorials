# Binary Search

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays); no prior algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

Binary search finds a target in a sorted array by repeatedly comparing it
to the middle element and discarding the half of the array that can't
contain it. This tutorial opens with a plain-English "guess the number
by always guessing the midpoint" analogy and a hand-traced 15-element
example before introducing any notation, then formally proves the `[lo,
hi)` loop invariant, derives the $\Theta(\log n)$ recurrence via both the
Master theorem and direct unrolling, and covers the classic
`(lo + hi) / 2` integer-overflow bug that shipped in real production code.
It also formally defines and implements the `lower_bound` / `upper_bound`
variants, showing precisely how their loop invariant differs from plain
equality search. All of this is confirmed against a **real, compiled C++
implementation** (`src/binary_search.cpp`) that is actually built with
`g++` and run via `subprocess` from the notebook — comparison counts and
timing are real measurements, not simulated numbers.

## Learning objectives

- Explain binary search's halving strategy and prove it correct using the
  `[lo, hi)` loop invariant (initialization, maintenance, termination).
- Derive the $\Theta(\log n)$ comparison bound both via the Master theorem
  and by direct unrolling of $T(n) = T(n/2) + \Theta(1)$.
- Implement and distinguish `lower_bound` and `upper_bound` from plain
  equality search, and state precisely how their invariants differ.
- Recognize and avoid the classic `(lo + hi) / 2` overflow bug.
- Compile and run a real C++ binary search implementation, and confirm its
  measured comparison counts track $\log_2 n$ across array sizes spanning
  six orders of magnitude, plotted on a log-scale axis.
- Know binary search's real-world tradeoffs: it requires sorted, randomly
  accessible data (so it doesn't help on linked lists or a single one-off
  unsorted lookup), and how it compares to interpolation search.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough, formal proofs,
  visuals (shrinking `[lo, hi]` interval, real benchmark plot), real
  compiled-C++ implementation and measurements, use cases (including
  `git bisect` and binary search "on the answer"), and limitations &
  debates
- `src/binary_search.cpp` — the real C++ implementation (equality search,
  `lower_bound`, `upper_bound`), compiled and run from the notebook.
  Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/binary_search.cpp -o src/binary_search.exe`

## References

- Knuth, D. E. *The Art of Computer Programming, Vol. 3: Sorting and
  Searching*, 2nd ed., Section 6.2.1.
- Bentley, J. *Programming Pearls*, 2nd ed., Column 4.
- Bloch, J. "Extra, Extra - Read All About It: Nearly All Binary Searches
  and Mergesorts are Broken," *Google Research Blog*, 2006.
- [cppreference: std::lower_bound](https://en.cppreference.com/w/cpp/algorithm/lower_bound)
- [cppreference: std::upper_bound](https://en.cppreference.com/w/cpp/algorithm/upper_bound)
