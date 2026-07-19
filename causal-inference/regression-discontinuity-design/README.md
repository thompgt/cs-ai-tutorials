# Regression Discontinuity Design

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic probability (expectation, conditional expectation), linear regression, and pandas familiarity; the [fundamental-problem-of-causal-inference](../fundamental-problem-of-causal-inference/) tutorial is helpful context but not required

## Summary

Not every treatment is randomized, but some are handed out by a known,
sharp rule based on a continuous number crossing a threshold — a test
score above a scholarship cutoff, a vote share above 50%, an age above a
legal drinking-age line. This tutorial builds **regression discontinuity
design (RDD)** from the ground up: the intuition that units just above and
just below a cutoff are "as good as randomized" relative to each other,
the formal **continuity assumption** that makes this rigorous, and the
derivation of why the resulting estimate is a **local average treatment
effect (LATE)** at the cutoff — not the population ATE. It distinguishes
**sharp** RDD (treatment is a deterministic function of the running
variable) from **fuzzy** RDD (crossing the cutoff only shifts the
*probability* of treatment, estimated via local instrumental variables),
explains via a live demonstration why high-order global polynomials are
bad practice (Gelman & Imbens, 2019) in favor of local linear regression
within a bandwidth, and applies the whole toolkit to a real, canonical
dataset: Lee's (2008) close U.S. House elections, estimating the causal
effect of a district electing a Democrat (vs. a Republican) by a razor-thin
margin on that representative's subsequent roll-call voting record.

## Learning objectives

- Explain, both intuitively and formally, why comparing units just above
  and below a known cutoff identifies a causal effect without full
  randomization.
- State the continuity-based identification assumption and derive the RDD
  estimand as a difference of one-sided limits.
- Explain why RDD identifies a **local** effect at the cutoff and why that
  scoping limitation is a real, important caveat for policy relevance.
- Distinguish sharp RDD from fuzzy RDD and connect fuzzy RDD to
  instrumental variables.
- Estimate a real discontinuity via local linear regression with a
  bandwidth, visualize it with the canonical binned-scatter RDD plot, check
  sensitivity to bandwidth choice, and run the standard running-variable
  manipulation/density diagnostic.

## Contents

- `tutorial.ipynb` — plain-English hook, a hand-built toy simulation
  showing the discontinuity directly, formal continuity-assumption/LATE
  derivation, a live comparison of global-polynomial vs. local-linear
  fitting (Gelman & Imbens critique), a real analysis of Lee's (2008)
  close-elections dataset (manipulation/density check, local linear
  regression with a bandwidth, the canonical binned-scatter RDD plot, and
  a bandwidth-sensitivity plot), use cases, and limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Thistlethwaite, D. L. & Campbell, D. T. (1960). *Regression-Discontinuity
  Analysis: An Alternative to the Ex Post Facto Experiment.* Journal of
  Educational Psychology, 51(6).
- Lee, D. S. (2008). *Randomized Experiments from Non-random Selection in
  U.S. House Elections.* Journal of Econometrics, 142(2).
- Lee, D. S., Moretti, E. & Butler, M. J. (2004). *Do Voters Affect or
  Elect Policies? Evidence from the U.S. House.* Quarterly Journal of
  Economics, 119(3).
- Imbens, G. W. & Lemieux, T. (2008). *Regression Discontinuity Designs: A
  Guide to Practice.* Journal of Econometrics, 142(2).
- Gelman, A. & Imbens, G. (2019). *Why High-Order Polynomials Should Not
  Be Used in Regression Discontinuity Designs.* Journal of Business &
  Economic Statistics, 37(3).
- Imbens, G. W. & Kalyanaraman, K. (2012). *Optimal Bandwidth Choice for
  the Regression Discontinuity Estimator.* Review of Economic Studies,
  79(3).
- Calonico, S., Cattaneo, M. D. & Titiunik, R. (2014). *Robust
  Nonparametric Confidence Intervals for Regression-Discontinuity
  Designs.* Econometrica, 82(6).
- McCrary, J. (2008). *Manipulation of the Running Variable in the
  Regression Discontinuity Design: A Density Test.* Journal of
  Econometrics, 142(2).
- Carpenter, C. & Dobkin, C. (2009). *The Effect of Alcohol Consumption on
  Mortality: Regression Discontinuity Evidence from the Minimum Drinking
  Age.* American Economic Journal: Applied Economics, 1(1).
- Cunningham, S. (2021). *Causal Inference: The Mixtape.* Yale University
  Press.
