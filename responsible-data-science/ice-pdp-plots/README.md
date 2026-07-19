# ICE and PDP Plots: Global and Local Feature Effects

**Domain:** `responsible-data-science`
**Level:** Intermediate
**Prerequisites:** supervised learning basics, comfort with expectation/conditioning
notation, scikit-learn familiarity

## Summary

Partial Dependence Plots (PDP, Friedman 2001) and Individual Conditional
Expectation curves (ICE, Goldstein et al. 2015) are the standard tools for
asking "how does this trained model's prediction change as one feature
changes?" — globally (PDP) and per-instance (ICE). This tutorial formally
derives the Monte Carlo approximation PDP actually computes, names and
demonstrates the independence assumption it silently relies on (with a
worked correlated-feature example showing PDP extrapolating into
combinations that never occur in real data), proves algebraically that PDP
is the pointwise mean of all ICE curves, and shows — with both a synthetic
example and a real, quantified finding on a trained gradient boosting
model — how that averaging step can hide strongly heterogeneous,
opposing-sign effects that centered ICE (c-ICE) reveals. It closes with why
Accumulated Local Effects (ALE, Apley & Zhu 2020) were proposed to fix the
correlated-feature problem, and why PDP/ICE are not causal quantities
despite superficially resembling one.

## Learning objectives

- State Friedman's partial dependence function
  $\hat f_S(x_S) = \frac{1}{n}\sum_i \hat f(x_S, x_C^{(i)})$, derive what
  the Monte Carlo sum is actually computing, and name its core independence
  assumption.
- Reproduce, numerically, a worked example of PDP extrapolating into
  impossible feature combinations when features are correlated — and
  quantify the same failure mode on a real, correlated feature pair
  (`AveRooms`/`AveBedrms`, $r \approx 0.85$) in the California Housing
  dataset.
- Define ICE curves formally, prove PDP is the pointwise average of all
  ICE curves, and use centered ICE (c-ICE) to detect heterogeneous,
  opposing-slope effects that a PDP's averaging can make look like "no
  effect."
- Train a real `HistGradientBoostingRegressor` on California Housing and
  compute real PDP, ICE, c-ICE, and a 2D interaction PDP with
  `sklearn.inspection.PartialDependenceDisplay` / `partial_dependence`,
  including a discovered real interaction (HouseAge's effect on price
  flips direction depending on occupancy/income).
- Explain why ALE plots average over conditional rather than marginal
  distributions to avoid the correlated-feature problem, and why PDP/ICE
  describe "what the model does," not a causal feature effect.

## Contents

- `tutorial.ipynb` — theory, visuals, implementation on the California
  Housing dataset, use cases, limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Friedman. *Greedy Function Approximation: A Gradient Boosting Machine*,
  2001.
- Goldstein, Kapelner, Bleich, Pitkin. *Peeking Inside the Black Box:
  Visualizing Statistical Learning with Plots of Individual Conditional
  Expectation*, 2015.
- Apley, Zhu. *Visualizing the Effects of Predictor Variables in Black Box
  Supervised Learning Models*, 2020.
- Molnar. *Interpretable Machine Learning* — chapters on PDP, ICE, ALE.
- Pace, Barry. *Sparse Spatial Autoregressions*, 1997 (source of the
  California Housing data).
- [scikit-learn: Partial Dependence and Individual Conditional Expectation
  plots](https://scikit-learn.org/stable/modules/partial_dependence.html)
