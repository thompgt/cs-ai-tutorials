# Randomized Experiments & Experimental Design

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** The fundamental-problem-of-causal-inference tutorial in
this domain (potential outcomes, ATE, ignorability); basic probability
(normal distribution, hypothesis testing) and pandas familiarity

## Summary

Randomization guarantees ignorability by construction — but that only
means the *comparison* is unbiased, not that the *experiment* was designed
well enough to answer the question it was built for. This tutorial covers
the engineering that has to happen before the coin flip: **power
analysis**, derived step by step from the sampling distribution of a
two-sample mean difference, to determine the sample size an experiment
needs (or the smallest effect a given sample size can detect, the
**minimum detectable effect**); **Type I/Type II errors** and the real
cost tradeoffs behind choosing significance level and power;
**stratified/blocked randomization**, which reduces estimator variance for
free by randomizing within strata of a prognostic covariate; and **cluster
randomization**, which taxes the effective sample size through the
**design effect** when individuals can't be independently randomized. All
of it is then run on a real randomized field experiment — Thornton
(2008)'s Malawi HIV-testing cash-incentive trial — including a
pre-registered-style balance check, a real power/MDE calculation using the
study's actual outcome variance and achieved sample size, and a real
treatment-effect estimate.

## Learning objectives

- Derive the sample-size and minimum-detectable-effect formulas for a
  two-sample difference-in-means test directly from its sampling
  distribution under the null and alternative hypotheses.
- Define Type I error, Type II error, and power precisely, and reason
  about the real-world tradeoffs behind choosing $\alpha$ and power for a
  given study.
- Explain why stratified/blocked randomization reduces variance (via the
  law of total variance) and why cluster randomization inflates the
  required sample size (via the design effect, $1+(m-1)\rho$).
- Run a real balance check, a real power/MDE analysis, and a real
  treatment-effect estimate on the Thornton (2008) HIV-testing incentive
  experiment, including the ITT vs. TOT/LATE distinction.

## Contents

- `tutorial.ipynb` — plain-English hook and a hand-built power simulation,
  the full power-analysis derivation (Type I/II errors, sample size/MDE
  formulas, stratified randomization, cluster randomization/design
  effect), illustrative power/MDE curves, a real analysis of the Thornton
  HIV-testing experiment (balance check, real power/MDE curves from the
  study's actual variance and sample size, dose-response effect
  estimates), use cases, and limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Thornton, R. (2008). *The Demand for, and Impact of, Learning HIV
  Status.* American Economic Review 98(5), 1829-1863.
- Cunningham, S. (2021). *Causal Inference: The Mixtape.* Yale University
  Press.
- Duflo, E., Glennerster, R., & Kremer, M. (2007). *Using Randomization in
  Development Economics Research: A Toolkit.* Handbook of Development
  Economics, Vol. 4.
- Gerber, A. S. & Green, D. P. (2012). *Field Experiments: Design,
  Analysis, and Interpretation.* W. W. Norton & Company.
- Cohen, J. (1988). *Statistical Power Analysis for the Behavioral
  Sciences* (2nd ed.). Lawrence Erlbaum Associates.
- Neyman, J. & Pearson, E. S. (1933). *On the Problem of the Most
  Efficient Tests of Statistical Hypotheses.* Philosophical Transactions
  of the Royal Society A, 231.
