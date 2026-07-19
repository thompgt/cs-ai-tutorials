# Instrumental Variables

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate-to-advanced rigor
**Prerequisites:** Basic OLS regression and covariance/correlation; the
fundamental-problem-of-causal-inference tutorial in this domain is a
helpful (not required) primer on confounding and ignorability

## Summary

Every method in this domain so far assumes you can measure your way out of
confounding — control for enough observed covariates and the bias goes
away. **Instrumental variables (IV)** is the strategy for when that's not
true: the confounder (e.g. "ability" in a schooling-and-wages question) is
unobserved and no amount of covariate adjustment can fix it. This tutorial
builds IV from a plain-English hook (distance to college as a lever on
schooling that has nothing to do with ability), states the three IV
assumptions — relevance, exclusion, exogeneity — as precise equations,
derives the **Wald estimator** and generalizes it to **Two-Stage Least
Squares (2SLS)**, and explains the **LATE (Local Average Treatment Effect)**
interpretation when treatment effects are heterogeneous (Imbens & Angrist,
1994). It then runs a real analysis of **Card's (1995)** schooling-and-wages
data, using proximity to a four-year college as the instrument: naive OLS,
a first-stage relevance/weak-instrument check, and a full 2SLS estimate via
`linearmodels.iv.IV2SLS` — including the honest result that this
specification's first-stage F-statistic falls short of the modern "F > 10"
weak-instrument threshold, and what that does to the 2SLS confidence
interval.

## Learning objectives

- State the three IV assumptions (relevance, exclusion restriction,
  exogeneity) precisely as equations, and explain why only relevance is
  directly testable from data.
- Derive the Wald estimator from the reduced-form/first-stage ratio, and
  generalize it algebraically to 2SLS with controls, including why
  regressing on the *predicted* treatment purges the endogeneity that
  biases naive OLS.
- Explain the LATE interpretation of IV under heterogeneous treatment
  effects, and the complier/always-taker/never-taker/defier typology.
- Run a real first-stage relevance check (with F-statistic) and a real
  2SLS estimate on Card's (1995) NLSYM data, and interpret an honest,
  imperfect result (weak instrument, wide confidence interval) rather than
  a cherry-picked clean one.
- Recognize the field's live, unresolved debates about IV: the
  untestability of the exclusion restriction, weak-instrument bias (Bound,
  Jaeger & Baker, 1995), and the instrument-specific nature of the LATE.

## Contents

- `tutorial.ipynb` — plain-English hook, a synthetic toy simulation showing
  naive OLS vs. the Wald estimator recovering the true effect, formal
  derivations of the three IV assumptions/Wald estimator/2SLS/LATE, visuals
  of the first-stage and reduced-form gaps, a real Card (1995) analysis
  (naive OLS baseline, first-stage relevance/weak-instrument check, 2SLS via
  `linearmodels`, OLS-vs-2SLS comparison plot), use cases, and limitations
  & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Card, D. (1995). *Using Geographic Variation in College Proximity to
  Estimate the Return to Schooling.* In L.N. Christofides, E.K. Grant, &
  R. Swidinsky (eds.), *Aspects of Labour Market Behaviour: Essays in
  Honour of John Vanderkamp.* University of Toronto Press.
- Angrist, J. D. & Krueger, A. B. (1991). *Does Compulsory School
  Attendance Affect Schooling and Earnings?* Quarterly Journal of
  Economics, 106(4).
- Imbens, G. W. & Angrist, J. D. (1994). *Identification and Estimation of
  Local Average Treatment Effects.* Econometrica, 62(2).
- Bound, J., Jaeger, D. A., & Baker, R. M. (1995). *Problems with
  Instrumental Variables Estimation When the Correlation Between the
  Instruments and the Endogenous Explanatory Variable Is Weak.* Journal of
  the American Statistical Association, 90(430).
- Staiger, D. & Stock, J. H. (1997). *Instrumental Variables Regression
  with Weak Instruments.* Econometrica, 65(3).
- Angrist, J. D. & Pischke, J.-S. (2009). *Mostly Harmless Econometrics: An
  Empiricist's Companion.* Princeton University Press.
- Cunningham, S. (2021). *Causal Inference: The Mixtape.* Yale University
  Press.
