# AVL Tree

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (recursion, pointers/references); helpful
but not required to have seen a plain binary search tree first (this repo's
binary-search-tree tutorial)
**Language:** Java (real, compiled, and executed — see `src/`)

## Summary

An AVL tree is a self-balancing binary search tree: every node tracks a
**balance factor** (its left subtree's height minus its right subtree's),
and after every insert or delete the tree walks back up and applies a
**rotation** the moment any node's balance factor leaves `{-1, 0, 1}`. This
tutorial opens with a "self-balancing bookshelf" analogy and a hand-traced
3-node example (a plain BST degenerating into a chain vs. an AVL tree fixing
it with one right rotation) before introducing any notation, then formally
states the AVL invariant, derives the four rotation cases (LL/RR/LR/RL), and
proves the tree's height is $O(\log n)$ via the Fibonacci-style
minimum-node-count recurrence $N(h) = N(h-1) + N(h-2) + 1$. All of this is
confirmed against a **real, compiled Java implementation**
(`src/AVLTree.java`) — real rotation diagrams and a real tree-height-vs-$n$
comparison against a plain BST are both built from the compiled program's
actual output, not simulated.

## Learning objectives

- Explain the AVL balance invariant and why a rotation restores it in $O(1)$
  time without changing the tree's sorted (in-order) order.
- Identify the four rotation cases (LL, RR, LR, RL) from a node's balance
  factor and where the newly inserted key landed.
- Prove, via the minimum-node recurrence $N(h) = N(h-1) + N(h-2) + 1$, that
  AVL tree height is bounded by $\approx 1.44 \log_2(n+2)$ — genuinely
  $O(\log n)$, not just "usually balanced."
- Compile and run a real Java AVL implementation, and confirm its measured
  height and rotation counts against the theoretical bound and against a
  plain (unbalanced) BST fed the identical worst-case sorted input.
- Know the real AVL-vs-red-black-tree tradeoff (tighter balance and faster
  lookups vs. more rebalancing work on writes) and why most production
  libraries (e.g. Java's `TreeMap`) pick red-black trees instead.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough (plain-BST chain
  vs. AVL rotation), formal proofs, real rotation diagrams and a real
  height-vs-n plot built from the compiled program's output, the Java
  implementation walkthrough with correctness checks, use cases, and
  limitations & debates
- `src/AVLTree.java` — the real Java implementation, compiled and run from
  the notebook. Build manually with:
  `javac src/AVLTree.java`
  and run any of its four modes (`avl`, `bst`, `trace`, `heights`) with:
  `java -cp src AVLTree <mode> [values...]` (values are read from stdin if
  omitted from the command line)

## References

- Adelson-Velsky, G. M. & Landis, E. M. *An algorithm for the organization
  of information*, Proceedings of the USSR Academy of Sciences, 1962 (the
  original algorithm; "AVL" is the authors' initials).
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  3rd/4th ed., Chapter 13 (balanced trees).
- Knuth, D. E. *The Art of Computer Programming, Volume 3: Sorting and
  Searching*, Section 6.2.3 (balanced trees).
- `src/AVLTree.java` in this tutorial's folder.
