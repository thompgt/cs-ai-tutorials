# Binary Heap / Priority Queue

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/lists); no prior algorithms background needed
**Language:** Java (real, compiled, and executed — see `src/`)

## Summary

A binary heap stores elements in a complete binary tree packed into a flat
array (index `i`'s children live at `2i+1` and `2i+2`), maintaining the
**heap property** — every parent `<=` both children — so the minimum is
always instantly available at the root. This tutorial opens with a
plain-English "ER triage line" analogy and a hand-traced 7-element build
before introducing any notation, then formally derives why a heap's height
is $O(\log n)$ *for free* (unlike a BST, which needs explicit rebalancing),
why `insert`/`extractMin` are $O(\log n)$ and `peek` is $O(1)$, and proves
the classic surprising result that **`heapify` builds a heap from an
unsorted array in $O(n)$, not $O(n \log n)$**, via the sum-of-heights
argument. All of this is confirmed against a **real, compiled Java
implementation** (`src/BinaryHeap.java`) that is actually built with
`javac` and run via `subprocess` from the notebook — the tree diagrams are
drawn from the compiled program's real internal array state, and the
comparison counts, swap counts, and timings are real measurements, not
simulated numbers.

## Learning objectives

- Explain how a heap keeps the minimum instantly accessible without being
  a fully sorted structure, and why the heap property (parent `<=`
  children) is sufficient for that.
- Derive why a complete binary tree of $n$ nodes has height $O(\log n)$
  automatically — contrasted with a BST, which needs explicit rebalancing
  to guarantee the same bound.
- Derive `insert`/`extractMin` as $O(\log n)$ (bounded by height) and
  `peek` as $O(1)$, and prove `heapify` runs in $O(n)$ via the
  sum-of-heights argument — the same trick that makes heapsort
  $O(n \log n)$ overall despite $n$ extractions.
- Compile and run a real Java binary heap implementation, draw its actual
  internal tree shape mid-build, and confirm the $O(n)$ vs. $O(n \log n)$
  heapify gap with real timings and real comparison counts.
- Know a heap's real-world tradeoffs against a BST (no efficient arbitrary
  search) and the live binary-vs-$d$-ary heap tuning choice used by some
  real schedulers.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a hand-traced
  build, formal proofs (height bound, $O(\log n)$ insert/extract, $O(n)$
  heapify), visuals (real tree diagrams from the compiled program's actual
  state, real heapify-vs-inserts benchmark), real compiled-Java
  implementation and measurements, use cases, limitations & debates
- `src/BinaryHeap.java` — the real Java implementation, compiled and run
  from the notebook. Build manually with:
  `javac src/BinaryHeap.java`
  and run with, e.g.:
  `java -cp src BinaryHeap trace`

## References

- Williams, J. W. J. *Algorithm 232 — Heapsort*, Communications of the ACM,
  1964.
- Floyd, R. W. *Algorithm 245 — Treesort 3*, Communications of the ACM,
  1964.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 6.
- `src/BinaryHeap.java` in this tutorial's folder.
