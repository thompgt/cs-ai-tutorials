---
name: notebook-quality
description: Quality bar for every tutorial notebook/report in this repo (cs-ai-tutorials) — mathematical rigor, real datasets with real computed results, critical/skeptical framing of each method's failure modes, and practitioner-grade code using standard libraries. Use whenever writing, reviewing, or revising a tutorial under any domain folder (math-and-statistics, machine-learning, responsible-data-science, etc.), before marking a tutorial's PR checklist complete, or when asked to draft/build/write a new tutorial.
---

# Notebook quality bar for cs-ai-tutorials

This repo's promise is that any tutorial takes a reader from "what is this"
through working code to "when would I actually reach for this, and where
does it break." Every tutorial — notebook or notebook+report — is judged
against the four pillars below. Depth target is **comprehensive**: a
45–90 minute read/work session per tutorial, not a quick-reference.

Apply this in addition to (not instead of) the structural requirements in
the repo's own `_template/` and `CONTRIBUTING.md`.

## The four pillars

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

1. **Intro** — what this is, why it matters, what you'll be able to do after.
2. **Theory** — formal definitions/derivations per pillar 1.
3. **Visuals** — at least one plot/diagram that builds intuition *before*
   the full implementation (not just result plots at the end).
4. **Implementation** — built incrementally, using real data (pillar 2)
   and real libraries (pillar 4).
5. **Use cases** — where this shows up in real systems.
6. **Limitations & debates** — required section per pillar 3.
7. **References** — papers, docs, or books actually cited in-text, not a
   generic reading list.

## Self-check before calling a tutorial done

Before marking a tutorial complete, verify:

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
