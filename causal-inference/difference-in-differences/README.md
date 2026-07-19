# Difference-in-Differences

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic probability and regression (OLS, interaction terms); familiarity with potential outcomes helpful (see the fundamental-problem-of-causal-inference tutorial) but not required

## Summary

When you can't randomize and you can't measure every confounder,
difference-in-differences (DiD) offers a different identification
strategy: compare the *change over time* in a treated group to the
*change over time* in a control group. This tutorial builds DiD from a
toy two-town minimum-wage example up to the formal **parallel trends
assumption**, algebraically derives the 2x2 DiD estimator from the
counterfactual argument, and proves — step by step, not by assertion —
that the 2x2 estimate is identical to the treatment×post interaction
coefficient in a two-way fixed effects (TWFE) regression. It then applies
all of this to the real Cheng & Hoekstra (2013) castle doctrine dataset:
a hand-computed 2x2 estimate and a matching TWFE regression estimate
(with a real confidence interval) on a Florida-vs-Washington state pair,
generalized to a clustered-standard-error TWFE regression across the full
50-state panel with staggered law adoption.

## Learning objectives

- Explain why comparing *changes* over time, not levels, nets out both
  fixed group differences and shared time trends.
- State the parallel trends assumption precisely, and explain why it is
  fundamentally untestable even though pre-trends can be checked.
- Derive the 2x2 DiD estimator from the counterfactual argument, and
  derive its algebraic equivalence to the TWFE regression interaction
  coefficient.
- Compute a real DiD estimate two ways (raw group means and regression)
  on real panel data, confirm they match, and obtain a real
  cluster-robust standard error and confidence interval.
- Recognize the staggered-adoption critique of naive TWFE (Goodman-Bacon,
  Callaway & Sant'Anna) well enough to know when a DiD regression can be
  badly biased.

## Contents

- `tutorial.ipynb` — plain-English two-town hook, formal parallel-trends
  and TWFE-equivalence derivations, a real parallel-trends plot and a
  2x2 geometry diagram built from real data, a full implementation on the
  Cheng & Hoekstra (2013) `castle.dta` panel (single-state-pair 2x2 +
  regression match, then a full staggered-adoption TWFE panel regression
  with clustered SEs), use cases, and limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Card, D. & Krueger, A.B. (1994). *Minimum Wages and Employment: A Case
  Study of the Fast-Food Industry in New Jersey and Pennsylvania.*
  American Economic Review 84(4).
- Cheng, C. & Hoekstra, M. (2013). *Does Strengthening Self-Defense Law
  Deter Crime or Escalate Violence? Evidence from Castle Doctrine.*
  Journal of Human Resources 48(3). (source of the `castle.dta` dataset
  used here)
- Goodman-Bacon, A. (2021). *Difference-in-Differences with Variation in
  Treatment Timing.* Journal of Econometrics 225(2).
- Callaway, B. & Sant'Anna, P.H.C. (2021). *Difference-in-Differences with
  Multiple Time Periods.* Journal of Econometrics 225(2).
- de Chaisemartin, C. & D'Haultfœuille, X. (2020). *Two-Way Fixed Effects
  Estimators with Heterogeneous Treatment Effects.* American Economic
  Review 110(9).
- Cunningham, S. (2021). *Causal Inference: The Mixtape.* Yale University
  Press. (source of the `castle.dta` distribution used here)
- Angrist, J. D. & Pischke, J.-S. (2009). *Mostly Harmless Econometrics.*
  Princeton University Press.
