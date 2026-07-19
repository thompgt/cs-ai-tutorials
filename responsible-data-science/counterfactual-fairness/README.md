# Counterfactual Fairness

**Domain:** `responsible-data-science`
**Level:** Advanced
**Prerequisites:** [`fairness-group-vs-individual`](../fairness-group-vs-individual/README.md) (demographic parity/equalized odds/individual fairness), basic probability and OLS regression, comfort with DAGs, pandas/scikit-learn familiarity

## Summary

Group fairness metrics (demographic parity, equalized odds, individual
fairness) are all statements about a joint distribution — they can be
audited from a labeled dataset alone. **Counterfactual fairness** (Kusner,
Loftus, Russell & Silva, NeurIPS 2017) asks a fundamentally different,
causal question: for *this specific individual*, would the model's
prediction have been different had their protected attribute been
different, holding everything about who they intrinsically are fixed? This
tutorial builds Pearl's structural causal model (SCM) framework from first
principles — causal graphs, structural equations, the `do`-operator, and
the abduction-action-prediction recipe for counterfactuals — states Kusner
et al.'s formal definition and the three-tier admissible-predictor
classification, and then builds an explicit, honestly-simplified linear
additive-noise SCM over the real UCI Adult Income dataset. Using that SCM,
it runs a genuine counterfactual audit of three trained classifiers (a
model that uses sex directly, a "fairness through unawareness" model that
drops it, and a Level-3 residual-feature model that is counterfactually
fair by construction), and uses `dice-ml` (DiCE) both for standard
individual counterfactual explanations and as a second, independent probe
of the protected attribute's direct effect. It closes with a dedicated
Limitations & debates section on causal-graph unidentifiability, the
utility cost of path-blocking, and the contested philosophical coherence of
counterfactual manipulation of social categories like race and sex.

## Learning objectives

- Formally define a structural causal model, the `do`-operator, and the
  abduction-action-prediction recipe for computing counterfactuals — and
  distinguish `do(X=x)` from conditioning on `X=x`.
- State Kusner et al.'s definition of counterfactual fairness precisely,
  and derive the three tiers of admissible predictors (non-descendants
  only; full counterfactual inference; deterministic additive-noise
  residual features).
- Explain concretely why a model can satisfy demographic parity or
  equalized odds while failing counterfactual fairness, and why
  counterfactual fairness requires committing to a causal graph that group
  and individual fairness never need.
- Build a simplified linear-SCM counterfactual audit pipeline end to end on
  real data, and correctly interpret the real numbers it produces
  (including the utility cost of enforcing it).
- Use `dice-ml` for both individual counterfactual explanations and a
  protected-attribute sensitivity probe, and understand why that probe,
  used alone, understates true counterfactual unfairness when the
  protected attribute acts mainly through mediators.
- Critically evaluate the framework: identifiability limits, the
  fairness/utility tradeoff of path-blocking, and the debate over whether
  "intervening on race" is a coherent counterfactual to ask about at all.

## Contents

- `tutorial.ipynb` — theory, visuals, implementation on UCI Adult Income,
  use cases, limitations & debates
- `src/` — none needed; all code is inline in the notebook

## Key results reproduced in the notebook

- Fitted on UCI Adult Income (30,162 rows after cleaning): `married`,
  `hours_per_week`, and `log_capital_gain` are all statistically significant
  descendants of `sex` in the fitted SCM (e.g. +43 percentage points on the
  linear-probability "married" equation); `education_num` is not
  (p = 0.65) and is treated as a non-descendant.
- A classifier that **never sees `sex` as a feature** ("fairness through
  unawareness") still has its predicted class flip for **14.6%** of
  held-out individuals under a full SCM-propagated counterfactual audit
  (`do(sex := 1-sex)`), because sex's effect survives through the mediators.
- A naive test that flips only the input `sex` column (no causal
  propagation) on the model that *does* use sex directly finds a flip rate
  of only **1.4%** — roughly a 9x understatement of the **15.5%** flip rate
  the full causal audit finds on the same model.
- A Level-3 predictor built on SCM residuals (the part of each mediator not
  explained by sex or its ancestors) achieves an exact **0%** counterfactual
  flip rate by construction, at a real, measured cost: test AUC drops from
  ~0.878 (aware/unaware models) to ~0.860.

## References

- Kusner, Loftus, Russell, Silva. *Counterfactual Fairness*. NeurIPS 2017.
- Pearl. *Causality: Models, Reasoning, and Inference*, 2nd ed. Cambridge
  University Press, 2009.
- Bareinboim, Correa, Ibeling, Icard. *On Pearl's Hierarchy and the
  Foundations of Causal Inference*, 2022.
- Kilbertus, Rojas-Carulla, Parascandolo, Hardt, Janzing, Schölkopf.
  *Avoiding Discrimination through Causal Reasoning*. NeurIPS 2017.
- Kasirzadeh, Smart. *The Use and Misuse of Counterfactuals in Ethical
  Machine Learning*. FAccT 2021.
- Kohler-Hausmann. *Eddie Murphy and the Dangers of Counterfactual Causal
  Thinking About Detecting Racial Discrimination*. Northwestern University
  Law Review, 2019.
- Mothilal, Sharma, Tan. *Explaining Machine Learning Classifiers through
  Diverse Counterfactual Explanations*. FAT* 2020 (`dice-ml`).
- Kohavi. *Scaling Up the Accuracy of Naive-Bayes Classifiers: a
  Decision-Tree Hybrid*. KDD 1996 (UCI Adult dataset).
- [`fairness-group-vs-individual`](../fairness-group-vs-individual/README.md) —
  the companion tutorial on demographic parity, equalized odds, and
  individual fairness, referenced throughout the theory section here.
