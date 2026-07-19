---
name: notebook-quality
description: Quality bar for every tutorial notebook/report in this repo (cs-ai-tutorials) — an accessible, beginner-friendly on-ramp before any rigor, mathematical rigor as a clearly-marked deep dive, real datasets with real computed results, critical/skeptical framing of each method's failure modes, and practitioner-grade code using standard libraries. Use whenever writing, reviewing, or revising a tutorial under any domain folder (math-and-statistics, machine-learning, responsible-data-science, etc.), before marking a tutorial's PR checklist complete, or when asked to draft/build/write a new tutorial.
---

# Notebook quality bar for cs-ai-tutorials

This repo's promise is that any tutorial takes a reader from "what is this"
through working code to "when would I actually reach for this, and where
does it break." Every tutorial — notebook or notebook+report — is judged
against the five pillars below. Depth target is **comprehensive in
coverage, not in difficulty**: a 45–90 minute read/work session per
tutorial is fine and expected, but a reader who has never heard of the
topic must be able to follow the first half without prior exposure to it.
**Comprehensive means "doesn't skip anything," not "assumes a PhD."**

Apply this in addition to (not instead of) the structural requirements in
the repo's own `_template/` and `CONTRIBUTING.md`.

## The five pillars

### 0. Accessible on-ramp (read this one first — it governs all the others)

Every tutorial opens with a **plain-English, beginner-friendly explanation**
before any formal notation appears. A reader who has never heard of the
topic should finish this opening section understanding *what problem this
solves* and *roughly how*, with zero equations required to get there.

- **Lead with an analogy or a concrete, relatable scenario**, not a
  definition. ("Imagine a loan officer who approves..." beats "Let
  $\hat{Y}$ be a binary classifier...".)
- **Show a tiny, runnable code snippet or a simple visual early** — within
  the first few sections — even before the real dataset/full implementation
  shows up later. A reader should see the idea *in action* before being
  asked to absorb theory.
- **Use text formatting to guide attention, not just to decorate**: bold
  the term being introduced the first time it's defined, use short
  paragraphs and bullets over dense blocks, and pull out the one-sentence
  "here's the takeaway" as its own bolded or blockquoted line when a
  section lands a key point.
- Write like you're explaining it to a smart friend who codes but has
  never seen this specific topic — not like you're writing a paper
  abstract. Avoid stacking multiple new terms in one sentence.
- **The formal math still belongs in the tutorial** (see pillar 1) — it
  is not cut, only moved and clearly labeled. Head the rigorous section
  with something like "## Going deeper: the formal definition" or "##
  The math, precisely" so a reader who wants the intuition-only version
  knows where they can stop, and a reader who wants the proof knows where
  to find it.

### 1. Mathematical rigor

### 1. Mathematical rigor

- State the formal definition before the intuition, or immediately after —
  never only intuition. If a metric or method has an equation, show the
  equation with every symbol defined.
- Derive, don't just cite, anything central to the topic (e.g. actually
  derive the Shapley value formula's fairness axioms, don't just say "it's
  from game theory"; actually write out the demographic parity /
  equalized odds constraints as equations, not prose).
- Use consistent notation across the whole tutorial, and reuse it correctly
  in the implementation section (variable names in code should trace back
  to symbols in the theory section where reasonable).
- Prove or at least sketch-prove non-obvious claims (e.g. why conformal
  prediction achieves marginal coverage; why Simpson's Paradox is possible
  algebraically, not just "it can happen").

### 2. Real datasets, real numbers

- Use real, open, well-known datasets appropriate to the topic — e.g.
  COMPAS recidivism, UCI Adult/Census Income, German Credit, Folktables,
  UCI Heart Disease, MIMIC-derived public subsets, or similarly recognized
  public datasets. Avoid `make_classification`/purely synthetic data as the
  primary example; synthetic data is acceptable only for a small
  illustrative aside (e.g. constructing a minimal Simpson's Paradox
  example) where a real dataset would obscure the point.
- Report actual computed numbers from the notebook run (actual fairness
  gaps, actual coverage rates, actual epsilon/utility tradeoffs) and
  interpret them honestly — including when the result is unflattering to
  the method or the model.
- State the dataset's provenance, size, and any known issues with it
  (e.g. COMPAS's documented critiques) since dataset flaws are often part
  of the responsible-data-science lesson itself.

### 3. Critical / skeptical framing

- Every tutorial must include an explicit **"Limitations & debates"**
  section distinct from "Use cases." Cover: known failure modes, common
  misuses in practice, and where the field disagrees (e.g. impossibility
  theorems for fairness metrics, SHAP's correlated-feature instability,
  the assumptions conformal prediction's coverage guarantee depends on).
- Don't present a method as a solved problem. If practitioners commonly
  misuse or over-trust it, say so directly and explain why.
- Where relevant, contrast the method against at least one alternative
  approach and state the tradeoff, not just "here's another option."

### 4. Practitioner code quality

- Implementation should use standard, actively-maintained libraries the
  way a practitioner would on the job (e.g. `fairlearn`, `aif360`, `shap`,
  `lime`, `alibi`/`dice-ml` for counterfactuals, `mapie` or `crepes` for
  conformal prediction, `PyCEbox`/`sklearn.inspection` for ICE/PDP,
  `diffprivlib`/`opacus` for differential privacy) rather than reimplementing
  everything from scratch as toy code.
- A from-scratch implementation is welcome *in addition to* the library
  usage when it materially builds intuition (e.g. hand-rolling a small
  Shapley value calculation on 3–4 features to make the combinatorics
  concrete before showing `shap.Explainer` on the full model) — but the
  tutorial should still show the real library, since that's what readers
  will actually use.
- Code should run top-to-bottom without manual fixes, use clear variable
  names, and include brief comments only where the *why* isn't obvious
  from the theory section already explaining the *what*.

## Required structure (in addition to `_template/`)

Each tutorial's `tutorial.ipynb` (and/or `report.md` for math-heavy splits)
must contain, in order:

1. **Intro** — a plain-English hook: what problem this solves, told through
   a relatable scenario or analogy, zero equations. What you'll be able to
   do after finishing.
2. **The idea, intuitively** — how it works, explained in plain language,
   with a simple visual and/or a tiny runnable code snippet shown early to
   make it concrete. This is the section a total beginner reads and comes
   away understanding the concept. Use bold on key terms and short,
   scannable paragraphs/bullets.
3. **Going deeper: the formal definition** (clearly headed as the
   rigor/deep-dive section) — formal definitions/derivations per pillar 1,
   for the reader who wants the proof, not required to "get" the concept.
4. **Visuals** — at least one plot/diagram that builds intuition *before*
   the full implementation (the intro-level visual from step 2 can count,
   but the implementation section should still build its own).
5. **Implementation** — built incrementally, using real data (pillar 2)
   and real libraries (pillar 4).
6. **Use cases** — where this shows up in real systems.
7. **Limitations & debates** — required section per pillar 3.
8. **References** — papers, docs, or books actually cited in-text, not a
   generic reading list.

## Compiled-language tutorials (e.g. `data-structures-algorithms`)

Some tutorials (algorithms implemented in Java or C++ rather than Python)
compile and run real code from the notebook via `subprocess`, instead of
running Python directly. The same pillars apply — pillar 4 ("practitioner
code quality") specifically means the Java/C++ source is a real,
compilable, idiomatic implementation, and pillar 2 ("real numbers") means
every reported number (comparisons, timings, output) comes from actually
executing the compiled binary, not a hand-written or simulated stand-in.

- Keep the Java/C++ source in `src/<name>.cpp` or `src/<name>.java`, and
  compile/run it from a notebook code cell with `subprocess` so the
  executed notebook shows the real compile step and real program output.
- **On this Windows dev machine, always compile C++ with static linking**:
  `g++ -O2 -std=c++17 -static -static-libgcc -static-libstdc++ file.cpp -o file.exe`.
  Plain dynamic linking intermittently fails with
  `collect2.exe: error: ld returned 116 exit status` due to a Windows
  Defender real-time-protection false positive on freshly-linked
  dynamically-linked MinGW binaries — this is unrelated to the C++ code's
  correctness and is not a real toolchain bug.
- Do not commit compiled binaries (`.exe`, `.o`, `.class`, etc.) — they're
  gitignored repo-wide. Only the source file(s), the executed notebook, and
  the README belong in the tutorial folder.
- Pick one language per algorithm based on fit (e.g. node-based/OOP-heavy
  structures suit Java; low-level/competitive-programming-style topics suit
  C++), not uniformly across the whole domain.
- Python is still used in the same notebook for visuals (matplotlib) and
  for driving/benchmarking the compiled binary — it does not need to also
  reimplement the algorithm.

## Build artifacts

If a `tutorial.ipynb` is generated programmatically (e.g. via an `nbformat`
build script), do not commit the build script itself — only the executed
notebook and `README.md` belong in the tutorial's folder, matching
`_template/`'s contents. Delete the build script once the notebook is
generated and verified.

## Self-check before calling a tutorial done

Before marking a tutorial complete, verify:

- [ ] A total beginner could read the intro + "idea, intuitively" sections
      and explain the concept back in their own words, without having read
      any equation.
- [ ] The formal/rigorous section is clearly headed as a deep dive (e.g.
      "Going deeper") and is not the *first* thing the reader hits.
- [ ] Bold and short paragraphs/bullets are used to highlight key terms and
      takeaways, not just default dense prose throughout.
- [ ] Every metric/method has a formal definition with defined notation.
- [ ] The dataset is real, named, sourced, and its numbers are the ones
      actually reported in the interpretive text (not placeholder numbers).
- [ ] There's a standalone "Limitations & debates" section with specific,
      named failure modes — not a generic "no method is perfect" paragraph.
- [ ] The implementation uses the standard library for this topic, and the
      code cell outputs are present (not cleared) so the notebook renders
      results on GitHub without execution.
- [ ] A reader with general programming background but no prior exposure
      to this specific topic could follow it end to end.
