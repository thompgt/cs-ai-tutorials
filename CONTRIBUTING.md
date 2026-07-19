# Contributing

Thanks for considering a contribution! This repo is meant to be a durable,
high-quality reference — favor depth and correctness over speed.

## Adding a new tutorial

1. Pick (or propose) a domain folder — see the table in [`README.md`](README.md).
2. Copy [`_template/`](_template) into `<domain>/<tutorial-name>/`, using a
   short kebab-case name (e.g. `gradient-descent`, `linked-lists`).
3. Fill in the tutorial `README.md` first — objectives, prerequisites, and a
   one-paragraph summary. This makes review much faster.
4. Build the content. Every tutorial should cover, at whatever depth the
   topic warrants:
   - **Theory** — the underlying math/concept, explained from first
     principles, not just formulas.
   - **Visuals** — plots, diagrams, or animations that build intuition.
   - **Implementation** — working code, built up incrementally with
     explanation, not a wall of a finished solution.
   - **Use cases** — where this shows up in real systems, and its
     limitations/tradeoffs.
5. Use a single notebook (`tutorial.ipynb`) for most topics. For math-dense
   topics where LaTeX-heavy derivations would clutter the notebook, split
   into `report.md` (theory) + `tutorial.ipynb` (implementation) and cross-link
   them.
6. Clear all notebook outputs before the final commit only if outputs are
   large/binary (images are fine and encouraged to keep); otherwise keep
   outputs so the notebook renders on GitHub without execution.
7. Add any new dependency to `environment.yml`, pinned to a major version.
8. Open a PR using the tutorial PR template — CI will execute your notebook
   headlessly to catch broken cells.

## Style guidelines

- Write for someone who knows general programming but not this specific
  topic. Define notation before using it.
- Prefer runnable, minimal code over abstracted "production" code — this is
  a learning resource, not a library.
- Cite sources for non-obvious claims or datasets (papers, docs, textbooks).
- Keep cells short; one idea per cell.

## Fixing or improving an existing tutorial

Typos, clearer explanations, better visuals, or updated implementations are
all welcome as regular PRs against the relevant folder.

## Requesting a topic

Open an issue using the "New tutorial request" template. Include why the
topic matters and, if you can, a rough outline.
