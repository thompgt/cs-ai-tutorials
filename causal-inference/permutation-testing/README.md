# Permutation Testing & Randomization Inference

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic probability (expectation, hypothesis testing) and pandas familiarity; helpful (not required) to have read the fundamental-problem-of-causal-inference tutorial first

## Summary

Every confidence interval and p-value in the fundamental-problem tutorial
relied on a modeling assumption: that the sampling distribution of the
estimator is approximately Normal, courtesy of the Central Limit Theorem.
This tutorial teaches the design-based alternative — **permutation testing
/ randomization inference** — which builds a null distribution directly
from the actual randomization mechanism that assigned treatment, with no
distributional or asymptotic assumptions at all. It states **Fisher's
sharp null hypothesis** precisely, derives the **exact permutation
p-value** and the **Fisher Randomization Test**, and applies it at two
scales on real data: full brute-force enumeration on Cunningham's tiny
8-row `ri.dta` teaching dataset, and 10,000-reshuffle Monte Carlo
approximation on the real National Supported Work (NSW) job-training
experiment, comparing the resulting p-value directly against the
OLS/HC1-based p-value from the fundamental-problem tutorial.

## Learning objectives

- State Fisher's sharp null hypothesis ($Y_i(1) = Y_i(0)$ for every unit)
  and explain why it lets every unit's counterfactual outcome be filled in
  for free, sidestepping the fundamental problem of causal inference.
- Derive the exact permutation p-value formula and explain when it's
  computed by full enumeration vs. approximated by Monte Carlo reshuffling.
- Build both an exact (small-$n$) and a Monte Carlo (large-$n$) permutation
  null distribution from real data, and read off a real p-value from each.
- Compare randomization inference against OLS/CLT-based inference directly,
  and explain the historical Fisher-vs-Neyman methodological fork.
- Know when permutation testing is the right tool (skewed metrics, small
  samples, complex/blocked randomization designs) and where it falls short
  (sharp null is a stronger claim than ATE=0; doesn't hand you a CI for
  free; requires correctly encoding the true randomization design).

## Contents

- `tutorial.ipynb` — plain-English hook, a tiny hand-enumerable toy example
  shown early, formal derivation of Fisher's sharp null and the exact
  permutation p-value, exact enumeration on the real `ri.dta` dataset (with
  the full 70-relabeling null distribution plotted and an honest
  not-significant result), Monte Carlo permutation testing (10,000
  reshuffles) on the real NSW experimental dataset compared directly
  against the OLS/HC1 p-value from the fundamental-problem tutorial, use
  cases, and limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Fisher, R. A. (1935). *The Design of Experiments.* Oliver & Boyd.
- Neyman, J. (1923/1990 translation). *On the Application of Probability
  Theory to Agricultural Experiments.* Statistical Science, 5(4).
- Rosenbaum, P. R. (2002). *Observational Studies*, 2nd ed. Springer.
- Imbens, G. W. & Rubin, D. B. (2015). *Causal Inference for Statistics,
  Social, and Biomedical Sciences.* Cambridge University Press.
- Cunningham, S. (2021). *Causal Inference: The Mixtape.* Yale University
  Press.
- Athey, S. & Imbens, G. W. (2017). *The Econometrics of Randomized
  Experiments.* In *Handbook of Economic Field Experiments*, Vol. 1.
- LaLonde, R. J. (1986). *Evaluating the Econometric Evaluations of
  Training Programs with Experimental Data.* American Economic Review,
  76(4).
