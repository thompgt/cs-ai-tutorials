# Differential Privacy

**Domain:** `responsible-data-science`
**Level:** Intermediate
**Prerequisites:** Basic probability (densities, expectation), Python/numpy/pandas, familiarity with logistic regression

## Summary

Differential privacy (DP) is a mathematically precise definition of "this
computation does not leak much about any single individual," together with
a toolbox of mechanisms that provably satisfy it. This tutorial formally
states the $(\varepsilon,\delta)$-DP definition, derives and proves the
Laplace mechanism achieves pure $\varepsilon$-DP, covers the Gaussian
mechanism and the composition theorems that make "privacy budget" a real,
depletable resource, and connects composition to why DP-SGD needs privacy
accounting. It then implements the Laplace mechanism from scratch on the
real UCI Adult Census Income dataset to empirically show the
accuracy/privacy tradeoff, and trains a real DP classifier with
`diffprivlib`'s `LogisticRegression` at several privacy budgets, comparing
it against a non-private `scikit-learn` baseline on the same data.

## Learning objectives

- State the formal $(\varepsilon,\delta)$-differential privacy definition,
  explain what "neighboring datasets" means, and explain precisely why the
  guarantee holds regardless of an adversary's side information.
- Derive global sensitivity and the Laplace mechanism, and prove it
  achieves pure $\varepsilon$-DP.
- Understand the Gaussian mechanism and why $(\varepsilon,\delta)$-DP is
  often the practical choice for repeated/vector-valued queries.
- State and justify the sequential and parallel composition theorems, and
  explain why they force real DP systems to track a depletable "privacy
  budget" (privacy accounting) — including the conceptual basis of DP-SGD.
- Quantitatively evaluate the real accuracy/privacy tradeoff of the Laplace
  mechanism and of a real differentially private classifier on a real
  dataset, at several $\varepsilon$ budgets.
- Critically evaluate a claim of "this system uses differential privacy": what
  epsilon was chosen, whether composition is tracked correctly, and what
  threat model DP does and does not cover (including its documented tension
  with fairness).

## Contents

- `tutorial.ipynb` — theory (formal DP definition, Laplace/Gaussian
  mechanisms with proof, composition theorems, DP-SGD), visuals,
  implementation on UCI Adult Census Income (hand-rolled Laplace mechanism
  + `diffprivlib` DP logistic regression vs. non-private baseline), use
  cases, limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Dwork, McSherry, Nissim, Smith. *Calibrating Noise to Sensitivity in
  Private Data Analysis*, TCC 2006.
- Dwork, Roth. *The Algorithmic Foundations of Differential Privacy*,
  Foundations and Trends in Theoretical Computer Science, 2014.
- Abadi, Chu, Goodfellow, McMahan, Mironov, Talwar, Zhang. *Deep Learning
  with Differential Privacy*, CCS 2016.
- Chaudhuri, Monteleoni, Sarwate. *Differentially Private Empirical Risk
  Minimization*, JMLR 2011.
- Bagdasaryan, Poursaeed, Shmatikov. *Differential Privacy Has Disparate
  Impact on Model Accuracy*, NeurIPS 2019.
- Mironov. *On Significance of the Least Significant Bits for Differential
  Privacy*, CCS 2012.
- Abowd. *The U.S. Census Bureau Adopts Differential Privacy*, KDD 2018.
- Kohavi. *Scaling Up the Accuracy of Naive-Bayes Classifiers: a
  Decision-Tree Hybrid*, KDD 1996 (UCI Adult / Census Income dataset).
- [`diffprivlib` documentation](https://diffprivlib.readthedocs.io) (IBM)
- [Opacus documentation](https://opacus.ai) (PyTorch DP-SGD library)
- [UCI Machine Learning Repository: Adult Data Set](https://archive.ics.uci.edu/ml/datasets/adult)
