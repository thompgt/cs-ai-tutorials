# Huffman Coding

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, recursion); binary trees and
min-heaps helpful but not required (see `binary-heap`)
**Language:** Java (real, compiled, and executed — see `src/`)

## Summary

Huffman coding builds an optimal binary prefix code for a set of symbol
frequencies by repeatedly merging the two least-frequent symbols (or
already-merged groups) into a new combined node, bottom-up, until one tree
remains — the same intuition behind Morse code giving common letters short
codes and rare letters long ones, done automatically and optimally for any
frequency distribution. This tutorial opens with the Morse code analogy
and a hand-traced six-symbol example (the classic CLRS `a,b,c,d,e,f` case)
before introducing any notation, then formally defines prefix-free codes,
proves why the greedy merge-the-two-smallest construction is optimal among
all prefix codes via an exchange argument, and derives the $O(n \log n)$
build time from `n - 1` min-heap merges. A real Huffman tree is built and
diagrammed from an actual short quote's letter frequencies, and a bar
chart compares fixed-width 8-bit ASCII against the **real measured**
Huffman-encoded bits-per-character from a **real, compiled Java
implementation** (`src/HuffmanCoding.java`) that is actually built with
`javac` and run via `subprocess` from the notebook — every code, encoded
bitstring, decoded output, and compression number is a real measurement,
not a simulated one.

## Learning objectives

- Explain why greedily merging the two least-frequent symbols builds a
  tree that gives common symbols short codes and rare symbols long codes.
- Define prefix-free (prefix) codes formally and explain why that
  property is exactly what makes a bitstream uniquely decodable without
  delimiters, and why any tree with symbols only at leaves guarantees it.
- Sketch-prove the Huffman optimality theorem via the exchange argument
  and greedy-choice/optimal-substructure induction, and derive the
  $O(n \log n)$ build time from `n - 1` min-heap merges.
- Compile and run a real Java Huffman implementation that encodes text to
  bits, decodes it back losslessly, and reports real compression numbers
  measured from actual output — not theoretical estimates.
- Know Huffman coding's real-world role as an entropy-coding *stage*
  (ZIP/DEFLATE, JPEG, MP3, fax compression) usually paired with an
  earlier redundancy-removal stage like LZ77, and its real limitations
  against the Shannon entropy bound and alternatives like arithmetic
  coding.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a hand-traced
  example, formal prefix-code definition and optimality proof sketch,
  visuals (a real Huffman tree diagram with codes labeled on edges, a real
  compression bar chart), real compiled-Java implementation and
  measurements, use cases, limitations & debates
- `src/HuffmanCoding.java` — the real Java implementation (frequency
  counting, min-heap tree construction, code generation, encode/decode
  round trip, compression stats), compiled and run from the notebook.
  Build manually with:
  `javac src/HuffmanCoding.java` then run with `java -cp src HuffmanCoding`
  (reads text from stdin, or from command-line arguments)

## References

- Huffman, D. A. *A Method for the Construction of Minimum-Redundancy
  Codes*, Proceedings of the IRE, 1952.
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  Chapter 16 (Greedy Algorithms).
- Shannon, C. E. *A Mathematical Theory of Communication*, Bell System
  Technical Journal, 1948.
