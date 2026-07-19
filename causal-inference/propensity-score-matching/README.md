# Propensity Score Matching

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** [The Fundamental Problem of Causal Inference](../fundamental-problem-of-causal-inference/) (potential outcomes, ATE, selection bias, ignorability); basic logistic regression and pandas familiarity

## Summary

Randomized experiments guarantee ignorability by construction — but most
real causal questions can't be randomized. This tutorial covers
**propensity score matching (PSM)**, the classic strategy for approximating
a randomized comparison out of observational data: estimate each unit's
probability of receiving treatment given its observed characteristics (the
**propensity score**), then compare treated units to *matched* control
units with a similar propensity score instead of to the whole,
systematically-different control pool. It states and sketch-proves
Rosenbaum & Rubin's (1983) key theorem — that matching on this single
scalar is, under **conditional ignorability** and **overlap**, as valid as
matching on every covariate at once — then runs the single most famous
demonstration in applied causal inference: LaLonde's (1986) NSW-vs-CPS
exercise. Using the same NSW experimental data as the previous tutorial
(so the true experimental ATE is known) paired against a large,
non-randomized CPS comparison pool, it shows with real numbers how badly a
naive observational comparison is biased, and how much of that bias
propensity score matching actually closes — honestly reporting that it
closes most, but not all, of the gap.

## Learning objectives

- Define the propensity score $e(x) = P(T=1\mid X=x)$ and sketch-prove
  Rosenbaum & Rubin's (1983) dimension-reduction theorem.
- Distinguish **conditional ignorability** (selection on observables) from
  the full randomization-based ignorability of the previous tutorial, and
  state the **overlap/common support** assumption PSM also requires.
- Estimate a propensity score via logistic regression, perform
  nearest-neighbor matching, and check covariate balance before and after
  on real data.
- Reproduce the LaLonde (1986) NSW-vs-CPS exercise end to end and compare
  the true experimental ATE, a naive observational estimate, and a
  PSM-matched estimate side by side, with real computed numbers.

## Contents

- `tutorial.ipynb` — plain-English hook, a toy self-selection simulation
  showing naive bias and how propensity matching corrects it, formal
  propensity-score/conditional-ignorability/overlap derivations with a
  sketch-proof of the Rosenbaum & Rubin theorem, before/after propensity
  score and covariate-balance visuals, a real analysis of the NSW (treated)
  + CPS (comparison pool) LaLonde exercise, use cases, and limitations &
  debates including the King & Nielsen (2019) critique
- `src/` — none needed; all code is inline in the notebook

## References

- Rosenbaum, P. R. & Rubin, D. B. (1983). *The Central Role of the
  Propensity Score in Observational Studies for Causal Effects.*
  Biometrika 70(1).
- LaLonde, R. J. (1986). *Evaluating the Econometric Evaluations of
  Training Programs with Experimental Data.* American Economic Review
  76(4).
- Dehejia, R. H. & Wahba, S. (1999). *Causal Effects in Nonexperimental
  Studies: Reevaluating the Evaluation of Training Programs.* JASA 94(448).
- Dehejia, R. H. & Wahba, S. (2002). *Propensity Score-Matching Methods for
  Nonexperimental Causal Studies.* Review of Economics and Statistics
  84(1).
- King, G. & Nielsen, R. (2019). *Why Propensity Scores Should Not Be Used
  for Matching.* Political Analysis 27(4).
- Stuart, E. A. (2010). *Matching Methods for Causal Inference: A Review
  and a Look Forward.* Statistical Science 25(1).
- Cunningham, S. (2021). *Causal Inference: The Mixtape.* Yale University
  Press. (source of the `nsw_mixtape.dta` and `cps_mixtape.dta` datasets
  used here)
- Imbens, G. W. & Rubin, D. B. (2015). *Causal Inference for Statistics,
  Social, and Biomedical Sciences.* Cambridge University Press.
