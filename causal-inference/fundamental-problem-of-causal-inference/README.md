# The Fundamental Problem of Causal Inference

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic probability (expectation, conditional expectation) and pandas familiarity; no prior causal-inference background needed

## Summary

Every causal question — did the drug work, did the ad campaign drive sales,
did the training program raise earnings — is secretly a comparison between
what happened and what *would have* happened otherwise, for the same unit,
at the same time. This tutorial formalizes that comparison using the
Neyman–Rubin **potential outcomes** framework, states the **fundamental
problem of causal inference** precisely (you observe exactly one of two
potential outcomes per unit, never both, for any unit, ever), and derives
algebraically why a naive comparison of treated vs. untreated groups is
biased by **selection bias** unless treatment assignment is independent of
the potential outcomes (**ignorability**). It shows why **randomization**
guarantees ignorability by construction, then verifies this on a real,
famous randomized experiment — the National Supported Work (NSW) job
training demonstration — checking covariate balance and estimating a real
Average Treatment Effect (ATE) with a 95% confidence interval.

## Learning objectives

- State the potential-outcomes definition of a causal effect ($Y_i(1)$,
  $Y_i(0)$, individual treatment effect) and the SUTVA assumption it relies
  on.
- Prove why individual causal effects are permanently unobservable, and
  derive the selection-bias decomposition of the naive group-mean
  comparison.
- Explain exactly why random assignment of treatment guarantees
  ignorability, and why that's the entire justification for RCTs being the
  causal-inference gold standard.
- Compute a real ATE (with SE/CI) from real experimental data, and run the
  standard pre-treatment covariate balance check every RCT analysis starts
  with.

## Contents

- `tutorial.ipynb` — plain-English hook, a hand-built "god's-eye view vs.
  observed reality" simulation showing the missing-data mask directly,
  formal potential-outcomes/SUTVA/ignorability derivations, visuals, a real
  analysis of the NSW experimental dataset (balance check + ATE estimate +
  distribution plot), use cases, and limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Neyman, J. (1923/1990). *On the Application of Probability Theory to
  Agricultural Experiments.* Statistical Science 5(4).
- Rubin, D. B. (1974). *Estimating Causal Effects of Treatments in
  Randomized and Nonrandomized Studies.* Journal of Educational Psychology
  66(5).
- Rubin, D. B. (1980). *Randomization Analysis of Experimental Data.* JASA
  75(371). (SUTVA)
- Holland, P. W. (1986). *Statistics and Causal Inference.* JASA 81(396).
- LaLonde, R. J. (1986). *Evaluating the Econometric Evaluations of
  Training Programs with Experimental Data.* American Economic Review
  76(4).
- Dehejia, R. H. & Wahba, S. (1999). *Causal Effects in Nonexperimental
  Studies.* JASA 94(448).
- Imbens, G. W. & Rubin, D. B. (2015). *Causal Inference for Statistics,
  Social, and Biomedical Sciences.* Cambridge University Press.
- Cunningham, S. (2021). *Causal Inference: The Mixtape.* Yale University
  Press.
- Angrist, J. D. & Pischke, J.-S. (2009). *Mostly Harmless Econometrics.*
  Princeton University Press.
