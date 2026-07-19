# SHAP and LIME: Local Model Explainability

**Domain:** `responsible-data-science`
**Level:** Intermediate
**Prerequisites:** Basic probability/expectation notation, classification
metrics (AUC, precision/recall), pandas/scikit-learn familiarity

## Summary

A single prediction from a gradient-boosted-tree or neural model is opaque
by default — no one can read "why" directly off thousands of internal
decision boundaries. This tutorial builds up the two dominant **local
explainability** methods from first principles: **SHAP**, which grounds
feature attribution in **Shapley values** from cooperative game theory and
derives the four axioms (efficiency, symmetry, dummy, additivity) that make
Shapley values the *unique* fair attribution rule, and **LIME**, which fits
a local, interpretable surrogate model by minimizing an explicit
fidelity + complexity objective. We formally compare what each method
guarantees (SHAP's local accuracy and consistency vs. LIME's lack of either
guarantee) and then apply the real `shap` (TreeExplainer/TreeSHAP) and
`lime` (LimeTabularExplainer) libraries to an XGBoost model trained on the
real UCI Adult/Census Income dataset, including a direct empirical
measurement of LIME's run-to-run explanation instability on a single fixed
prediction.

## Learning objectives

- Derive the Shapley value formula from the four cooperative-game-theory
  axioms and compute one by brute-force enumeration on a toy 3-feature game.
- Formally state SHAP's additive feature attribution framework, the
  KernelSHAP vs. TreeSHAP distinction, and the local accuracy / consistency
  properties SHAP satisfies by construction.
- Formally state LIME's local surrogate objective
  ($\mathcal{L}(f,g,\pi_x) + \Omega(g)$) and explain the fidelity/complexity
  tradeoff it encodes and the free hyperparameters (kernel width, sampling)
  it depends on.
- Apply `shap.TreeExplainer` and `lime.lime_tabular.LimeTabularExplainer`
  to a real trained model and read/interpret summary, waterfall, and
  local-explanation plots and their underlying numbers.
- Explain, with cited evidence, why SHAP and LIME can disagree on the same
  prediction, why LIME's explanations are not deterministic, and why
  neither method by itself satisfies a regulatory "right to explanation."

## Contents

- `tutorial.ipynb` — theory, visuals, implementation on UCI Adult/Census
  Income with XGBoost + SHAP + LIME, use cases, limitations & debates

## References

- Shapley, L. S. (1953). *A Value for n-Person Games*.
- Lundberg, S. M., & Lee, S.-I. (2017). *A Unified Approach to Interpreting
  Model Predictions*. NeurIPS.
- Lundberg, S. M., et al. (2020). *From Local Explanations to Global
  Understanding with Explainable AI for Trees*. Nature Machine Intelligence.
- Ribeiro, M. T., Singh, S., & Guestrin, C. (2016). *"Why Should I Trust
  You?": Explaining the Predictions of Any Classifier*. KDD.
- Kumar, I. E., Venkatasubramanian, S., Scheidegger, C., & Friedler, S.
  (2020). *Problems with Shapley-value-based explanations as feature
  importance measures*. ICML.
- Alvarez-Melis, D., & Jaakkola, T. S. (2018). *On the Robustness of
  Interpretability Methods*. arXiv:1806.08049.
- Wachter, S., Mittelstadt, B., & Floridi, L. (2017). *Why a Right to
  Explanation of Automated Decision-Making Does Not Exist in the General
  Data Protection Regulation*. International Data Privacy Law, 7(2).
- Kohavi, R., & Becker, B. (1996). *UCI Adult / Census Income Data Set*.
  UCI Machine Learning Repository.
- [SHAP documentation](https://shap.readthedocs.io)
- [LIME repository](https://github.com/marcotcr/lime)
- GDPR, Article 22 and Recital 71.
