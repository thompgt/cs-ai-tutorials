# Trie (Prefix Tree)

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/maps); no prior algorithms background needed
**Language:** Java (real, compiled, and executed — see `src/`)

## Summary

A trie stores words one character per node, so a path from the root spells
a prefix and words that share a prefix share the same tree path — the
autocomplete "type 'ca', see every word starting with it" behavior falls
directly out of that structure. This tutorial opens with a plain-English
phone-search-bar hook and a hand-traced 5-word example (`cat`, `car`,
`card`, `care`, `dog`) using a nested-dict Python mock before any notation,
then formally defines a trie over an alphabet $\Sigma$, proves `insert`,
`search`, and `startsWith` are all $O(L)$ — independent of how many words
$n$ are stored — and explicitly contrasts this against a `HashSet<String>`,
which matches a trie on exact-match speed but cannot answer prefix
questions without an $O(n \cdot L)$ full scan. All of this is confirmed
against a **real, compiled Java implementation** (`src/Trie.java`) that is
actually built with `javac` and run via `subprocess` from the notebook —
the trie-structure diagram is drawn from the compiled program's own `DUMP`
output, and the prefix-search-vs-linear-scan benchmark uses real
nanosecond timings from the same binary, not simulated numbers.

## Learning objectives

- Explain how a trie stores words by walking/creating one node per
  character, and why shared prefixes share tree structure.
- State the formal definition of a trie over an alphabet $\Sigma$ and
  prove that `insert`, `search`, and `startsWith` run in $O(L)$ time,
  independent of the number of stored words $n$.
- Explain precisely why a hash set of strings matches a trie on exact-match
  lookup but cannot efficiently answer prefix queries.
- Compile and run a real Java trie implementation, and confirm its
  measured prefix-count timings stay near-flat as the dictionary grows,
  while a naive linear scan's timings grow with $n$.
- Know a trie's real-world tradeoffs — memory overhead per node, when a
  compressed trie (radix/Patricia tree) is the practical fix, and when a
  plain hash set is the simpler, comparably fast choice.

## Contents

- `tutorial.ipynb` — intro analogy, intuitive walkthrough with a
  nested-dict Python mock, formal definition and complexity proofs,
  visuals (a real trie-structure diagram drawn from the compiled
  program's output, a real benchmark plot), real compiled-Java
  implementation and measurements, use cases, limitations & debates
- `src/Trie.java` — the real Java implementation (`insert`, `search`,
  `startsWith`, `countWordsWithPrefix`, plus a naive linear-scan baseline
  for benchmarking), compiled and run from the notebook. Build manually
  with:
  `javac src/Trie.java`
  and run with:
  `java -cp src Trie < input.txt`

## References

- de la Briandais, R. *File Searching Using Variable Length Keys*, Western
  Joint Computer Conference, 1959.
- Fredkin, E. *Trie Memory*, Communications of the ACM, 1960 (coined the
  name "trie").
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS) —
  tries exercises.
- `src/Trie.java` in this tutorial's folder.
