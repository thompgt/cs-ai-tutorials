# Causal Graphs (DAGs)

**Domain:** `causal-inference`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic probability and pandas familiarity; the
[Fundamental Problem of Causal Inference](../fundamental-problem-of-causal-inference/tutorial.ipynb)
tutorial is a natural predecessor but not required — this tutorial is
self-contained

## Summary

Most causal questions don't come from a randomized experiment — they come
from observational data, where you have to state your own assumptions
about what causes what before any statistical adjustment can be trusted.
This tutorial introduces **causal directed acyclic graphs (DAGs)** as the
graphical language for stating those assumptions precisely. It covers the
three canonical 3-node building blocks (**chain/mediator**,
**fork/confounder**, **collider**), defines **d-separation** and proves
(with intuition and a live numeric simulation) why conditioning on a
confounder removes bias while conditioning on a collider *creates* it, and
states Pearl's **backdoor criterion** for picking a valid adjustment set.
It then applies all of this to a real dataset — maternal smoking and birth
weight (`cattaneo2.dta`) — computing a naive (unadjusted) estimate, a
correct backdoor-adjusted estimate, and a deliberately wrong estimate from
adjusting for a descendant of the outcome, showing exactly how and why the
numbers move.

## Learning objectives

- Read and draw a causal DAG: nodes as variables, arrows as direct causal
  claims, and recognize the chain, fork, and collider structures.
- Define d-separation and explain why conditioning on a non-collider blocks
  a path while conditioning on a collider (or its descendant) opens one —
  demonstrated with a numeric "talent and looks among celebrities"
  simulation.
- State Pearl's backdoor criterion precisely and use it to select a valid
  adjustment set from a DAG, rather than "controlling for everything
  available."
- Compute a real naive vs. backdoor-adjusted causal estimate from
  observational data (maternal smoking's effect on birth weight), and show
  numerically what happens when the adjustment set is wrong (adjusting for
  a descendant of the outcome).

## Contents

- `tutorial.ipynb` — plain-English hook, a numeric collider-bias
  simulation (talent/looks/celebrity), formal d-separation and
  backdoor-criterion derivations, `networkx`-drawn DAG visuals, a real
  analysis of the Cattaneo (2010) maternal-smoking/birth-weight dataset
  (naive vs. backdoor-adjusted vs. wrongly-adjusted estimates), use cases,
  and limitations & debates (including the Pearl vs. Rubin/Imbens
  DAG-vs.-potential-outcomes discussion)
- `src/` — none needed; all code is inline in the notebook

## References

- Pearl, J. (2009). *Causality: Models, Reasoning, and Inference* (2nd
  ed.). Cambridge University Press.
- Pearl, J. (1988). *Probabilistic Reasoning in Intelligent Systems.*
  Morgan Kaufmann. (introduces d-separation)
- Pearl, J. (1993). *Comment: Graphical Models, Causality, and
  Intervention.* Statistical Science 8(3). (backdoor criterion)
- Pearl, J. & Mackenzie, D. (2018). *The Book of Why: The New Science of
  Cause and Effect.* Basic Books.
- Greenland, S., Pearl, J., & Robins, J. M. (1999). *Causal Diagrams for
  Epidemiologic Research.* Epidemiology 10(1).
- Imbens, G. W. (2020). *Potential Outcome and Directed Acyclic Graph
  Approaches to Causality: Relevance for Empirical Practice in Economics.*
  Journal of Economic Literature 58(4).
- Cattaneo, M. D. (2010). *Efficient Semiparametric Estimation of
  Multi-Valued Treatment Effects Under Ignorability.* Journal of
  Econometrics 155(2). (source of the `cattaneo2.dta` dataset used here)
- Cunningham, S. (2021). *Causal Inference: The Mixtape.* Yale University
  Press.
- Holland, P. W. (1986). *Statistics and Causal Inference.* JASA 81(396).
