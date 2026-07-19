# Topic Modeling with Latent Dirichlet Allocation (LDA)

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python; basic probability (distributions) helpful
but not required; no prior NLP or topic-modeling background needed

## Summary

Given a pile of thousands of unlabeled documents, can an algorithm
automatically discover that some are "about sports," some "about
politics," some "about technology" — and represent each individual
document as a *mixture* of these discovered themes rather than a single
hard label? This tutorial introduces **unsupervised topic modeling** in
contrast to every supervised tutorial elsewhere in this domain, states the
**LDA generative story** (Blei, Ng & Jordan, 2003) precisely — per-document
topic mixtures $\theta_d \sim \text{Dirichlet}(\alpha)$, per-topic word
distributions $\phi_k \sim \text{Dirichlet}(\beta)$ — explains why exact
inference is intractable and which approximate method (online variational
Bayes) `gensim` actually uses, then trains a real `gensim.models.LdaModel`
on 3,000 real AG News articles. Discovered topics are validated against
the dataset's real (never-trained-on) category labels via a cross-tabulated
alignment table, and the number-of-topics choice is justified with real
computed **coherence scores** ($C_v$) rather than guessing.

## Learning objectives

- Explain what a "topic" is in LDA (a probability distribution over words)
  and why documents are treated as topic *mixtures*, not single labels.
- State the LDA generative story precisely, and explain intuitively what
  the Dirichlet distribution's concentration parameters ($\alpha$, $\beta$)
  control.
- Explain why exact LDA inference is intractable, and name the approximate
  inference method `gensim.models.LdaModel` uses.
- Train a real LDA model with `gensim`, choose the number of topics using
  coherence score, and honestly evaluate discovered topics against real
  ground-truth labels.
- Know when LDA is the right tool versus its limitations and the modern
  neural alternative (BERTopic).

## Contents

- `tutorial.ipynb` — plain-English hook and a toy 2-topic (food vs. space)
  example run through real `gensim` LDA, the formal generative-story
  derivation and Dirichlet intuition, why exact inference is intractable
  and gensim's online variational Bayes approximation, real preprocessing
  and LDA training on 3,000 AG News articles, coherence-score comparison
  of K=4 vs. K=8 topics, top-words-per-topic bar charts, a real
  discovered-topic-vs-true-category cross-tabulation and heatmap, use
  cases, and limitations & debates (interpretability, choosing K, bag-of-
  words assumption, neural topic models)
- `src/` — none needed; all code is inline in the notebook

## References

- Blei, D.M., Ng, A.Y., Jordan, M.I. (2003). *Latent Dirichlet Allocation.*
  Journal of Machine Learning Research, 3, 993-1022.
- Hofmann, T. (1999). *Probabilistic Latent Semantic Indexing.* SIGIR 1999.
- Hoffman, M., Blei, D.M., Bach, F. (2010). *Online Learning for Latent
  Dirichlet Allocation.* NeurIPS 2010.
- Röder, M., Both, A., Hinneburg, A. (2015). *Exploring the Space of Topic
  Coherence Measures.* WSDM 2015.
- Grootendorst, M. (2022). *BERTopic: Neural topic modeling with a
  class-based TF-IDF procedure.* arXiv:2203.05794.
- Zhang, X., Zhao, J., LeCun, Y. (2015). *Character-level Convolutional
  Networks for Text Classification.* NeurIPS 2015 — source of the AG News
  dataset.
- `gensim` documentation: `gensim.models.LdaModel`,
  `gensim.models.CoherenceModel`, `gensim.corpora.Dictionary`.
