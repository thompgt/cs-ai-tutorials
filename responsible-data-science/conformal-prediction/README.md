# Conformal Prediction

**Domain:** `responsible-data-science`
**Level:** Intermediate / Advanced
**Prerequisites:** Basic probability (quantiles, conditional probability), regression and classification with scikit-learn

## Summary

A point prediction says nothing about how much to trust it. Conformal
prediction wraps *any* trained regressor or classifier so it also outputs a
prediction interval or prediction set with a distribution-free, finite-sample
coverage guarantee. This tutorial formally defines exchangeability (the
actual assumption conformal prediction needs — weaker than i.i.d.),
nonconformity scores, and the split (inductive) conformal algorithm,
proves the marginal coverage guarantee $P(Y_{n+1}\in C(X_{n+1})) \ge
1-\alpha$ from exchangeability and quantile thresholding, and applies it
with the `mapie` library to a real gradient-boosted regressor on the
California Housing dataset (basic split-conformal vs. Conformalized
Quantile Regression) and a real random forest classifier on the UCI
handwritten digits dataset (LAC vs. Adaptive Prediction Sets). Empirical
coverage on held-out test data is checked against the nominal target
throughout, and the tutorial ends by showing — with real numbers — that
marginal coverage can silently hide subgroup-level miscoverage, directly
connecting to this repo's fairness tutorial.

## Learning objectives

- Define exchangeability precisely, distinguish it from i.i.d., and explain
  why it — not i.i.d. — is what the conformal coverage proof actually uses.
- Derive the split conformal algorithm and prove
  $P(Y_{n+1}\in C(X_{n+1})) \ge 1-\alpha$ from exchangeability of
  nonconformity scores and quantile thresholding.
- Build real regression prediction intervals (absolute-residual score) and
  classification prediction sets (LAC and Adaptive Prediction Sets) with
  `mapie`, and verify empirical coverage against the nominal target on
  held-out data.
- Formally distinguish marginal from conditional coverage, explain why
  exact conditional coverage is generally unattainable (Barber et al. 2021),
  and implement Mondrian (group-conditional) conformal prediction as the
  practical middle ground.
- Derive why basic split-conformal intervals have provably constant width
  while Conformalized Quantile Regression (Romano, Patterson & Candès,
  2019) adapts width to local difficulty, and confirm this on real data as
  a function of a difficulty-correlated feature.
- Know the concrete failure modes: exchangeability breaking under
  distribution shift/time series, marginal coverage hiding subgroup
  under-coverage (a fairness issue), and the common misreading of coverage
  as a per-interval probability rather than a long-run procedural guarantee.

## Contents

- `tutorial.ipynb` — theory, visuals, implementation on California Housing
  (regression) and UCI handwritten digits (classification), use cases,
  limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Vovk, Gammerman & Shafer. *Algorithmic Learning in a Random World*.
  Springer, 2005 (2nd ed. 2022).
- Papadopoulos, Proedrou, Vovk & Gammerman. *Inductive Confidence Machines
  for Regression*, ECML 2002.
- Romano, Patterson & Candès. *Conformalized Quantile Regression*, NeurIPS
  2019.
- Romano, Sesia & Candès. *Classification with Valid and Adaptive
  Coverage*, NeurIPS 2020.
- Barber, Candès, Ramdas & Tibshirani. *The Limits of Distribution-Free
  Conditional Predictive Inference*, Information and Inference 2021.
- Tibshirani, Barber, Candès & Ramdas. *Conformal Prediction Under
  Covariate Shift*, NeurIPS 2019.
- Gibbs & Candès. *Adaptive Conformal Inference Under Distribution Shift*,
  NeurIPS 2021.
- Xu & Xie. *Conformal Prediction Interval for Dynamic Time-Series*
  (EnbPI), ICML 2021.
- Angelopoulos & Bates. *A Gentle Introduction to Conformal Prediction and
  Distribution-Free Uncertainty Quantification*, arXiv:2107.07511.
- [MAPIE documentation](https://mapie.readthedocs.io)
- This repo's `responsible-data-science/fairness-group-vs-individual`
  tutorial — referenced for the marginal-vs-subgroup coverage / fairness
  connection.
