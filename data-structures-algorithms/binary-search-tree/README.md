# Binary Search Tree

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, recursion helpful but not required); no prior algorithms background needed
**Language:** Java (real, compiled, and executed — see `src/`)

## Summary

A binary search tree stores each value in a node with at most two
children, maintaining the invariant that every left-subtree value is
smaller than its parent and every right-subtree value is bigger — which
makes an in-order traversal produce sorted output for free and lets
search/insert/delete each throw away half the remaining tree with every
comparison. This tutorial opens with a plain-English "filing cabinet of
folders" analogy and a hand-traced 8-value example before introducing any
notation, then formally proves the in-order-traversal-is-sorted claim by
induction, derives the $O(h)$ complexity of search/insert/delete in terms
of tree height $h$, and works through deletion's three cases (leaf,
one child, two children via in-order-successor replacement) with an
explicit correctness argument for the trickiest one. All of this is
confirmed against a **real, compiled Java implementation**
(`src/BST.java`) that is actually built with `javac` and run via
`subprocess` from the notebook — the tree diagrams, heights, node counts,
and deletion traces shown are real program output, not simulated numbers.

## Learning objectives

- Explain why a BST's insertion rule (smaller left, bigger right,
  everywhere) is exactly what makes in-order traversal yield sorted order,
  and prove it by induction on the BST invariant.
- Explain why search/insert/delete cost is $O(h)$ — proportional to tree
  *height*, not node count — and why that height can be $\Theta(\log n)$
  (balanced) or degrade to $\Theta(n)$ (e.g. sorted insertion order),
  motivating self-balancing variants like AVL and red-black trees.
- Walk through deletion's three cases, including the correctness argument
  for why replacing a two-children node's value with its in-order
  successor preserves the BST invariant.
- Compile and run a real Java BST implementation, draw the real tree it
  builds, and confirm its measured height on random vs. sorted insertion
  order tracks $\log_2 n$ vs. $n$ respectively.
- Know where BSTs are actually used in production (`java.util.TreeMap`'s
  red-black tree, symbol tables, ordered range queries) and why a plain,
  unbalanced BST is rarely deployed as-is.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough, formal proofs,
  visuals (a real tree diagram and a real height-vs-n benchmark plot), the
  real compiled-Java implementation with a live demonstration of all three
  deletion cases, use cases, limitations & debates
- `src/BST.java` — the real Java implementation, compiled and run from the
  notebook. Build manually with:
  `javac src/BST.java` and run with `java -cp src BST`

## References

- Knuth, D. E. *The Art of Computer Programming, Volume 3: Sorting and
  Searching*, 2nd ed.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 12.
- [java.util.TreeMap documentation](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/util/TreeMap.html)
  (red-black tree internally).
