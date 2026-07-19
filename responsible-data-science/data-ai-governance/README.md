# Data & AI Governance

**Domain:** `responsible-data-science`
**Level:** Intermediate
**Prerequisites:** `fairness-group-vs-individual` (we reuse its dataset and
metric definitions), basic pandas/scikit-learn familiarity

## Summary

A fairness metric or a privacy guarantee is only as trustworthy as the
organizational process around it: can you trace which data trained the
model, is there real documentation, did anyone check the numbers before
deployment, and does anything re-check them after? This tutorial covers the
process, documentation, and legal infrastructure that makes the technical
guarantees from the rest of this domain enforceable rather than optional —
data lineage/provenance, Model Cards (Mitchell et al. 2019) and Datasheets
for Datasets (Gebru et al. 2021) with a real, fully filled-out example of
each, the EU AI Act's risk-tier system, GDPR Article 22 (and the real scope
limits of its so-called "right to explanation," per Wachter, Mittelstadt &
Floridi 2017), the NIST AI Risk Management Framework, and model risk
governance in practice (risk tiering, model inventories, pre-deployment
review gates, post-deployment monitoring). The implementation section
builds a real Model Card and Datasheet for a freshly trained COMPAS
classifier and a real, runnable pre-deployment governance gate that reads a
`fairlearn` fairness report against a stated policy and returns an actual
pass/fail result computed on held-out data.

## Learning objectives

- Explain what data lineage/provenance is (PROV-DM's Entity/Activity/Agent
  model) and why it's a precondition for auditing any downstream fairness
  or privacy claim.
- Write a complete Model Card and a complete Datasheet for a real
  model/dataset pair, covering every section each framework actually
  requires.
- State precisely what the EU AI Act's four risk tiers require (with real
  examples in each tier), what GDPR Article 22 does and does not guarantee,
  and what each of the NIST AI RMF's four functions (Govern, Map, Measure,
  Manage) actually covers.
- Build and run a pre-deployment governance gate that checks a trained
  model's real fairness metrics against a stated policy and returns a real
  pass/fail decision.
- Explain why passing a governance gate does not guarantee counterfactual
  fairness or other deeper properties covered elsewhere in this repo, and
  why algorithmic impact assessments are frequently reduced to compliance
  checkboxes in practice.

## Contents

- `tutorial.ipynb` — theory, visuals, implementation (lineage log, Model
  Card, Datasheet, governance gate on a real trained COMPAS classifier),
  use cases, limitations & debates

## References

- Mitchell, M. et al. (2019). *Model Cards for Model Reporting*. FAT* 2019.
- Gebru, T. et al. (2021). *Datasheets for Datasets*. CACM, 64(12).
- W3C. (2013). *PROV-DM: The PROV Data Model*.
- European Union. *Regulation (EU) 2024/1689 (Artificial Intelligence
  Act)* — Article 5, Annex III, Articles 9–15, 43, 50.
- European Union. *GDPR (Regulation (EU) 2016/679)*, Article 22, Recital 71.
- Wachter, S., Mittelstadt, B., & Floridi, L. (2017). *Why a Right to
  Explanation of Automated Decision-Making Does Not Exist in the GDPR*.
  International Data Privacy Law, 7(2).
- NIST. (2023). *AI Risk Management Framework (AI RMF 1.0)*. NIST AI 100-1.
- Federal Reserve / OCC. (2011). *Supervisory Guidance on Model Risk
  Management*, SR 11-7 / OCC 2011-12.
- Metcalf, J. et al. (2021). *Algorithmic Impact Assessments and
  Accountability: The Co-construction of Impacts*. FAccT 2021.
- Raji, I.D., & Buolamwini, J. (2019). *Actionable Auditing*. AIES 2019.
- Raji, I.D. et al. (2020). *Closing the AI Accountability Gap*. FAT* 2020.
- Angwin, J., Larson, J., Mattu, S., & Kirchner, L. (2016). *Machine Bias*.
  ProPublica.
- [ProPublica compas-analysis dataset & methodology](https://github.com/propublica/compas-analysis)
- [Fairlearn documentation](https://fairlearn.org)
