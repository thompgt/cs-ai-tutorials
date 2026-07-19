# Fairness: Group vs. Individual Notions

**Domain:** `responsible-data-science`
**Level:** Intermediate
**Prerequisites:** Basic classification metrics (confusion matrix, TPR/FPR), pandas/scikit-learn familiarity

## Summary

"Fairness" is not one metric — it's a family of mathematically incompatible
definitions. This tutorial builds up the two major families, **group
fairness** (demographic parity, equalized odds, equal opportunity,
predictive parity) and **individual fairness** (Dwork et al.'s "similar
individuals should be treated similarly"), derives why several of the most
intuitive group metrics cannot all be satisfied at once when base rates
differ across groups (the fairness impossibility results), and measures all
of them on the real ProPublica COMPAS recidivism dataset using `fairlearn`.

## Learning objectives

- Formally define demographic parity, equalized odds, equal opportunity,
  and predictive parity, and compute each on a real model.
- Formally define individual fairness (Lipschitz condition) and compute a
  practical proxy for it (kNN consistency score).
- Understand *why* group and individual fairness — and even different group
  metrics from each other — can be mutually incompatible, via the
  Chouldechova / Kleinberg-Mullainathan-Raghavan impossibility results.
- Know which fairness definition fits which real-world context, and where
  each one is commonly misapplied.

## Contents

- `tutorial.ipynb` — theory, visuals, implementation on COMPAS, use cases,
  limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Dwork, Hardt, Pitassi, Reingold, Zemel. *Fairness Through Awareness*, 2012.
- Chouldechova. *Fair Prediction with Disparate Impact*, 2017.
- Kleinberg, Mullainathan, Raghavan. *Inherent Trade-Offs in the Fair
  Determination of Risk Scores*, 2016.
- Barocas, Hardt, Narayanan. *Fairness and Machine Learning: Limitations
  and Opportunities*. fairmlbook.org, 2023.
- Angwin, Larson, Mattu, Kirchner. *Machine Bias*, ProPublica, 2016.
- [Fairlearn documentation](https://fairlearn.org)
