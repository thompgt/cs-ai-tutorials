# Causal Inference

Experiment design, causal graphs, and treatment effect estimation methods.

## Tutorials

| Tutorial | What it covers |
|---|---|
| [The Fundamental Problem of Causal Inference](fundamental-problem-of-causal-inference) | Potential outcomes, SUTVA, ATE/ATT/ATC, why individual effects are unobservable, and why randomization guarantees ignorability — verified on the real NSW job-training RCT |
| [Causal Graphs](causal-graphs) | DAGs, d-separation, chain/fork/collider structures, Pearl's backdoor criterion; real collider-bias simulation and confounding adjustment on maternal-smoking/birth-weight data |
| [Randomized Experiments & Experimental Design](randomized-experiments) | Power analysis, MDE, stratified and cluster randomization; power/effect estimation on a real Malawi HIV-testing incentive RCT |
| [Propensity Score Matching](propensity-score-matching) | Rosenbaum-Rubin theorem, conditional ignorability, nearest-neighbor matching; the classic LaLonde NSW/CPS exercise showing naive OLS badly biased and PSM closing most of the gap |
| [Difference-in-Differences](difference-in-differences) | Parallel trends, the 2x2/two-way-fixed-effects equivalence, staggered-adoption critique; real castle-doctrine-law analysis |
| [Regression Discontinuity Design](regression-discontinuity-design) | Sharp RDD, continuity-based identification, local linear estimation and bandwidth sensitivity; real close-elections analysis |
| [Instrumental Variables](instrumental-variables) | Wald estimator, 2SLS derivation, LATE/complier framework, weak instruments; real Card (1995) schooling-wages analysis |
| [Permutation Testing & Randomization Inference](permutation-testing) | Fisher's sharp null, exact permutation p-values, Monte Carlo randomization inference vs. asymptotic OLS inference |
| [Uplift Modeling](uplift-modeling) | Conditional Average Treatment Effects, the response-modeling fallacy, T/S/X-learners, qini curves; real heterogeneous-effect estimation on a marketing RCT |

See [CONTRIBUTING.md](../CONTRIBUTING.md) to add another.
