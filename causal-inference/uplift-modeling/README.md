# Uplift Modeling: Heterogeneous Treatment Effects (CATE)

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** The Fundamental Problem of Causal Inference tutorial in
this domain (potential outcomes, ATE, ignorability); basic `scikit-learn`
familiarity

## Summary

An average treatment effect can hide as much as it reveals: a marketing
email that "works on average" might be doing nothing for customers who
would have converted anyway, actively annoying others, and only genuinely
persuading a third group. This tutorial introduces **uplift modeling** —
estimating the **Conditional Average Treatment Effect (CATE)**,
$\tau(x) = E[Y(1)-Y(0)\mid X=x]$, a function of a unit's characteristics
rather than one population-wide number. It formally derives the
**response-modeling fallacy** (why ranking by predicted outcome probability
is not the same as ranking by uplift), presents the standard **meta-learner**
framework (T-learner, S-learner, and the X-learner's propensity-weighted
idea, explicitly connected back to the propensity-score-matching tutorial's
propensity score), and builds real CATE estimators — both a from-scratch
`scikit-learn` T-learner and an `EconML` `TLearner` — on a real randomized
email-marketing experiment. It evaluates the resulting targeting model with
a **qini curve**, the standard practitioner tool for this problem, computed
for real from held-out predictions and outcomes.

## Learning objectives

- State the CATE, $\tau(x)$, precisely, and derive how it relates to the
  ATE ($\text{ATE} = E_x[\tau(x)]$).
- Prove why a response model ($P(Y=1\mid X,T=1)$) is not a valid proxy for
  uplift, and recognize the "sure thing" / "persuadable" / "sleeping dog"
  failure modes this causes in practice.
- Build a T-learner and an S-learner, and explain the X-learner's use of
  the propensity score to reweight between them (Künzel et al., 2019).
- Fit real meta-learners with both hand-written `scikit-learn` code and
  `EconML`, and evaluate them with a qini curve on a real dataset.
- Explain why CATE estimation still requires the same ignorability
  assumption as every earlier tutorial in this domain — and why violations
  of it are harder to detect at the CATE level than at the ATE level.

## Contents

- `tutorial.ipynb` — plain-English hook (persuadables/sure
  things/lost causes/sleeping dogs), formal CATE/response-modeling-fallacy/
  meta-learner derivations, a synthetic illustrative visual of $\tau(x)$ as
  a function, a real analysis of Matheus Facure's `invest_email_rnd.csv`
  randomized email-marketing dataset (balance check, ATE baseline,
  from-scratch and EconML T-learners, CATE distribution plot, qini curve),
  use cases, and limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Künzel, S. R., Sekhon, J. S., Bickel, P. J., & Yu, B. (2019).
  *Metalearners for Estimating Heterogeneous Treatment Effects using
  Machine Learning.* PNAS 116(10).
- Radcliffe, N. J. & Surry, P. D. (2011). *Real-World Uplift Modelling with
  Significance-Based Uplift Trees.* Portrait Technical Report.
- Wager, S. & Athey, S. (2018). *Estimation and Inference of Heterogeneous
  Treatment Effects using Random Forests.* JASA 113(523).
- Curth, A. & van der Schaar, M. (2021). *Nonparametric Estimation of
  Heterogeneous Treatment Effects: From Theory to Learning Algorithms.*
  AISTATS 2021.
- Facure, M. *Causal Inference for the Brave and True*
  (matheusfacure.github.io/python-causality-handbook) — source of the
  `invest_email_rnd.csv` dataset used here.
- Battocchi, K. et al. (2019). *EconML: A Python Package for ML-Based
  Heterogeneous Treatment Effects Estimation.* Microsoft Research.
  github.com/py-why/econml.
- Holland, P. W. (1986). *Statistics and Causal Inference.* JASA 81(396).
