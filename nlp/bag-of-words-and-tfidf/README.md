# Bag-of-Words & TF-IDF

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python; helpful (not required) to have read the
*Tokenization & Text Preprocessing* tutorial in this domain first

## Summary

Every search engine, document classifier, and clustering pipeline that
predates (and often still competes with) neural NLP relies on one core
idea: representing a document as a vector over the vocabulary, the
**vector space model**. This tutorial builds that representation from
scratch, starting with raw **bag-of-words** counts and showing exactly why
they fail (common words like "the" dominate), then derives **TF-IDF**
term by term — term frequency, inverse document frequency, and why the
$\log(N/\text{df})$ form specifically down-weights corpus-wide common
words — and defines **cosine similarity** and why it (not Euclidean
distance) is the standard way to compare document vectors. Everything is
demonstrated on a real dataset: 2,000 articles from the **AG News**
4-class topic dataset, with a real `TfidfVectorizer` matrix, real
highest-TF-IDF terms per class, and a real nearest-neighbor-by-cosine-
similarity retrieval demo that correctly groups articles by topic with no
labels used in the similarity computation itself.

## Learning objectives

- Build a bag-of-words vector and explain precisely what it discards.
- Derive TF-IDF's three components (TF, IDF, and their product) and
  explain why each piece of the IDF formula — the $N/\text{df}$ ratio, the
  $+1$ smoothing, and the $\log$ — is there.
- Define cosine similarity and explain why it's invariant to document
  length in a way Euclidean distance isn't.
- Build a real TF-IDF search/retrieval system and measure how often
  "most similar by cosine similarity" agrees with "same true topic."
- State TF-IDF's real limitations (word-order blindness, sparsity, no
  semantic similarity between synonyms) and where the field went next.

## Contents

- `tutorial.ipynb` — plain-English hook, a hand-built bag-of-words example
  showing the "the" problem, a full derivation of TF/IDF/TF-IDF and cosine
  similarity, an IDF-curve visual, a real TF-IDF matrix built on AG News
  with top terms per class (bar charts), a real query-based retrieval demo
  plus corpus-wide nearest-neighbor topic-agreement accuracy, a 2D SVD
  projection colored by true topic, use cases, and limitations & debates
  (word-order blindness, sparsity, no synonym awareness, the BM25/neural
  retrieval debate)
- `src/` — none needed; all code is inline in the notebook

## References

- Salton, G. & Buckley, C. (1988). *Term-weighting approaches in automatic
  text retrieval.* Information Processing & Management, 24(5), 513–523.
- Robertson, S. & Zaragoza, H. (2009). *The Probabilistic Relevance
  Framework: BM25 and Beyond.* Foundations and Trends in Information
  Retrieval, 3(4), 333–389.
- Manning, C.D., Raghavan, P., Schütze, H. (2008). *Introduction to
  Information Retrieval*, Chapters 6 & 7. Cambridge University Press.
- Zhang, X., Zhao, J., LeCun, Y. (2015). *Character-level Convolutional
  Networks for Text Classification.* NeurIPS 2015. (Source of the AG News
  dataset.)
- scikit-learn documentation. `sklearn.feature_extraction.text.TfidfVectorizer`,
  `sklearn.metrics.pairwise.cosine_similarity`.
