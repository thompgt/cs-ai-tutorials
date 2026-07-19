# Knuth-Morris-Pratt (KMP) String Matching

**Domain:** `data-structures-algorithms`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic programming (loops, arrays/strings); no prior algorithms background needed
**Language:** C++ (real, compiled, and executed — see `src/`)

## Summary

KMP searches for a pattern inside a text without ever re-reading a text
character it's already consumed. This tutorial opens with a plain-English
"Ctrl+F" hook contrasting the naive sliding-window search (which throws
away a partial match and restarts on every mismatch) against KMP's key
idea: precompute a **failure function** on the pattern alone that says
exactly how much of a partial match can be reused after a failure. It
hand-traces the failure function and a small search by hand, formally
defines the "longest proper prefix which is also a suffix" (LPS) failure
function, derives *why* it lets the search skip re-comparisons (not just
assert it), gives an amortized-analysis argument for why building the
failure function is $O(m)$, and proves the search's text pointer never
moves backward — the invariant behind the overall $O(n+m)$ bound. All of
this is confirmed against a **real, compiled C++ implementation**
(`src/kmp.cpp`) that runs both naive search and KMP side by side, actually
built with `g++` and run via `subprocess` from the notebook — match
positions, comparison counts, and timings are real measurements, not
simulated numbers.

## Learning objectives

- Explain why naive string search is $O(nm)$ in the worst case, with a
  concrete adversarial example (`"AAAA...A"` text vs `"AAAA...AAB"`
  pattern).
- Hand-trace the failure function (LPS array) for a small pattern and
  explain, with a derivation (not just an assertion), why it lets KMP
  reuse previously-matched characters instead of re-comparing them.
- Prove the text pointer in KMP's search never moves backward, and use
  that invariant plus an amortized two-pointer argument to derive the
  overall $O(n + m)$ bound.
- Compile and run a real C++ implementation that runs naive search and
  KMP side by side, cross-checks that they find identical match
  positions, and confirms the measured comparison-count gap between them
  on both typical and adversarial input.
- Know KMP's real-world tradeoffs against Boyer-Moore (typical-case speed
  vs. guaranteed worst-case bound) and where a guaranteed linear bound
  actually matters (e.g. security-sensitive scanning) vs. where it
  doesn't (ordinary text search).

## Contents

- `tutorial.ipynb` — intro Ctrl+F hook, intuitive walkthrough with a hand-
  traced failure function, formal LPS definition and correctness proof,
  amortized-analysis argument for the failure function's $O(m)$ build,
  visuals (step-by-step match visualization contrasting naive vs. KMP,
  real benchmark plot on typical and adversarial input), real compiled-
  C++ implementation and measurements, use cases, limitations & debates.
- `src/kmp.cpp` — the real C++ implementation, compiled and run from the
  notebook. Implements naive search and KMP (failure function + linear
  search) side by side, each instrumented to count comparisons and time
  itself. Build manually with:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ src/kmp.cpp -o src/kmp.exe`

## References

- Knuth, D.E., Morris, J.H., Pratt, V.R. *Fast Pattern Matching in
  Strings*, SIAM Journal on Computing, 6(2), 1977 (the original KMP
  paper).
- Boyer, R.S., Moore, J.S. *A Fast String Searching Algorithm*,
  Communications of the ACM, 20(10), 1977 (the practical alternative
  discussed in Limitations & debates).
- Cormen, Leiserson, Rivest & Stein. *Introduction to Algorithms* (CLRS),
  3rd/4th ed., Chapter 32 (String Matching).
- `src/kmp.cpp` in this tutorial's folder — the real, compiled
  implementation used for every measurement in the notebook.
