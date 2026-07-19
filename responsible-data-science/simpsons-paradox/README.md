# Simpson's Paradox

**Domain:** `responsible-data-science`
**Level:** Intermediate
**Prerequisites:** Basic probability (conditional probability, weighted averages), pandas familiarity; basic exposure to DAGs is helpful but not required (introduced here)

## Summary

Simpson's Paradox is the phenomenon where a trend that holds in every
subgroup of a dataset reverses — or disappears — once the subgroups are
pooled together. This tutorial formalizes the paradox as a precise
probabilistic statement, derives *why* it is arithmetically possible with a
fully worked $2\times2\times2$ numeric example, and then resolves it using
Judea Pearl's causal DAG framework: whether the aggregated or the
stratified number is the one you should trust depends entirely on whether
the third variable is a confounder, a mediator, or a collider. It
reproduces the two most famous real-world instances of the paradox — the
1973 UC Berkeley graduate admissions data and the Charig et al. (1986)
kidney stone treatment study — with the actual historical counts, and
closes with a direct discussion of how the paradox is a concrete, documented
failure mode of naive group-fairness audits.

## Learning objectives

- State the precise probabilistic condition under which per-group and
  pooled trends can point in opposite directions, and derive why this is
  always arithmetically possible (it's a property of weighted averages,
  not a statistical anomaly).
- Explain, using a causal DAG, why the paradox is not actually paradoxical
  once you know the causal structure connecting the variable of interest,
  the outcome, and the stratifying variable — and why it is genuinely
  ambiguous without one.
- Correctly compute and interpret both the aggregate and per-stratum
  admission/success rates on two real, historical datasets, including a
  logistic-regression check that the "sex effect" in the Berkeley data
  changes sign once department is controlled for.
- Recognize when Simpson's Paradox threatens the validity of an A/B test,
  a clinical trial, or a fairness audit, and know the decision rule for
  when to stratify vs. when to look at the aggregate.

## Contents

- `tutorial.ipynb` — theory, a worked $2\times2\times2$ numeric example,
  causal DAG diagrams (confounder / mediator / collider), the real UC
  Berkeley 1973 admissions analysis (aggregate rates, per-department rates,
  and a logistic regression sign-flip check), the real Charig et al. (1986)
  kidney stone dataset, use cases, and limitations & debates
- `src/` — none needed; all code is inline in the notebook

## References

- Simpson, E. H. *The Interpretation of Interaction in Contingency Tables*.
  Journal of the Royal Statistical Society, Series B, 1951.
- Bickel, Hammel, O'Connell. *Sex Bias in Graduate Admissions: Data from
  Berkeley*. Science 187(4175), 1975.
- Charig, Webb, Payne, Wickham. *Comparison of Treatment of Renal Calculi by
  Open Surgery, Percutaneous Nephrolithotomy, and Extracorporeal Shock Wave
  Lithotripsy*. BMJ 292(6524), 1986.
- Julious, Mullee. *Confounding and Simpson's Paradox*. BMJ 309:1480, 1994.
- Pearl. *Causality: Models, Reasoning, and Inference*, 2nd ed. Cambridge
  University Press, 2009.
- Pearl, Mackenzie. *The Book of Why: The New Science of Cause and Effect*.
  Basic Books, 2018.
- Berkson. *Limitations of the Application of Fourfold Table Analysis to
  Hospital Data*. Biometrics Bulletin 2(3), 1946.
- R Core Team. `datasets::UCBAdmissions` — Student Admissions at UC
  Berkeley. R Documentation.
- See also this repo's `fairness-group-vs-individual` (group fairness
  metrics) and `counterfactual-fairness` (SCM/DAG framing) tutorials.
