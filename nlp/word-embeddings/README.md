# Word Embeddings (word2vec)

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python; helpful (not required) to have gone through
this domain's `bag-of-words-and-tfidf` tutorial first

## Summary

TF-IDF and bag-of-words represent every distinct word as its own dimension,
so any two distinct words are orthogonal by construction — the
representation has no way to know "cat" and "dog" are related. This
tutorial introduces **word embeddings** as the fix: dense, low-dimensional
vectors learned from the contexts a word appears in (the **distributional
hypothesis**, Firth 1957 — "you shall know a word by the company it
keeps"). It derives the **word2vec skip-gram objective** precisely,
explains why the full softmax is computationally infeasible at vocabulary
scale, and derives **negative sampling** as the practical fix, including
the exact loss. A real `gensim.models.Word2Vec` skip-gram model is trained
on a real ~1.2M-token corpus (three Jane Austen novels, the King James
Bible, and three Shakespeare tragedies, via NLTK's Gutenberg corpus), then
used for real nearest-neighbor lookups, a real (honestly-reported, only
partially successful) king/queen analogy-arithmetic attempt, and a real
PCA projection showing semantic clustering by category (royalty, family,
places, conflict). The tutorial closes with word2vec's core limitation —
one static vector per word regardless of sense — which motivates the
contextual embeddings (BERT) covered later in this domain, plus the
well-documented social-bias and analogy-evaluation debates around it.

## Learning objectives

- Explain the distributional hypothesis and why dense embeddings capture
  word similarity that sparse TF-IDF/bag-of-words vectors structurally
  cannot.
- State the skip-gram objective and softmax probability precisely, explain
  why the full softmax doesn't scale, and derive the negative-sampling loss
  that fixes it.
- Explain intuitively why linear vector arithmetic
  ($\vec{king}-\vec{man}+\vec{woman}\approx\vec{queen}$) can capture
  relational structure, and evaluate that claim honestly on a real trained
  model rather than assuming it always works.
- Train a real word2vec model with `gensim`, inspect nearest neighbors, and
  visualize the embedding space with PCA.
- Name word2vec's core limitation (static, one-vector-per-word embeddings)
  and its connection to contextual embeddings (ELMo/BERT), plus the
  documented social-bias and analogy-evaluation debates.

## Contents

- `tutorial.ipynb` — plain-English hook contrasting TF-IDF's orthogonal
  word vectors with dense embeddings, a hand-counted toy co-occurrence demo,
  the formal skip-gram/negative-sampling derivation, a real `gensim`
  Word2Vec model trained on NLTK Gutenberg text (Austen + KJV Bible +
  Shakespeare), real nearest-neighbor tables, an honestly-reported real
  analogy-arithmetic attempt, a real PCA scatter plot of curated semantic
  categories, use cases, and limitations & debates (static embeddings vs.
  contextual embeddings, encoded social bias, analogy-evaluation
  methodology critique)
- `src/` — none needed; all code is inline in the notebook

## References

- Mikolov, T., Chen, K., Corrado, G., Dean, J. (2013). *Efficient
  Estimation of Word Representations in Vector Space.* arXiv:1301.3781.
- Mikolov, T., Sutskever, I., Chen, K., Corrado, G., Dean, J. (2013).
  *Distributed Representations of Words and Phrases and their
  Compositionality.* NeurIPS 2013.
- Firth, J.R. (1957). *A Synopsis of Linguistic Theory, 1930–1955.* In
  Studies in Linguistic Analysis, Philological Society, Oxford.
- Bolukbasi, T., Chang, K-W., Zou, J., Saligrama, V., Kalai, A. (2016).
  *Man is to Computer Programmer as Woman is to Homemaker? Debiasing Word
  Embeddings.* NeurIPS 2016.
- Linzen, T. (2016). *Issues in Evaluating Semantic Spaces Using Word
  Analogies.* Proceedings of the 1st Workshop on Evaluating Vector-Space
  Representations for NLP (RepEval), ACL 2016.
- Pennington, J., Socher, R., Manning, C.D. (2014). *GloVe: Global
  Vectors for Word Representation.* EMNLP 2014.
- Řehůřek, R. & Sojka, P. `gensim` — Topic Modelling for Humans.
  `gensim.models.Word2Vec` documentation.
- NLTK Project. `nltk.corpus.gutenberg` documentation.
