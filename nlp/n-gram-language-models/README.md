# N-gram Language Models

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python, basic probability (conditional probability);
no prior NLP background needed

## Summary

An n-gram language model predicts the next word from the previous $n-1$
words by counting how often word sequences occurred in real text and
turning those counts into probabilities. This tutorial derives the chain
rule of probability, the Markov assumption that makes n-gram counting
tractable, the Maximum Likelihood Estimate, and **perplexity** (the
standard language-modeling evaluation metric) from scratch — then builds
real unigram, bigram, and trigram models, hand-implemented from counts, on
the **Brown corpus** (NLTK's genre-diverse, tagged 1960s American English
corpus). It measures real held-out perplexity, hits the **zero-probability
problem** on a genuine unseen trigram, derives **Laplace/add-k smoothing**
as the fix, shows Laplace smoothing actually over-smoothing on real data,
and verifies the **Kneser-Ney** continuation-count intuition (the "San
Francisco" example) directly against corpus counts. It closes by
generating sample text from the trained bigram/trigram models — locally
plausible, globally incoherent — which sets up exactly why RNN/LSTM and
transformer language models (elsewhere in this domain) exist.

## Learning objectives

- State the chain rule of probability and derive the Markov assumption
  that reduces it to a tractable n-gram approximation.
- Derive the Maximum Likelihood Estimate for n-gram probabilities from
  counts, and define/derive perplexity as exponentiated average
  negative log-likelihood.
- Explain the zero-probability problem concretely, and derive Laplace /
  add-k smoothing as a fix — including why it can over-smooth in practice.
- Explain (conceptually) why Kneser-Ney smoothing's continuation-count
  backoff beats naive frequency-based backoff.
- Build unigram/bigram/trigram models from scratch on real text, measure
  how perplexity changes with $n$ and with smoothing strength, and
  generate text from the trained models.

## Contents

- `tutorial.ipynb` — plain-English hook, from-scratch bigram counting on a
  toy corpus, formal derivations (chain rule, Markov assumption, MLE,
  perplexity, Laplace/add-k smoothing, Kneser-Ney intuition), a Zipf's-law
  visual on the real Brown corpus, from-scratch unigram/bigram/trigram
  models trained/evaluated on a real train/test split of Brown corpus
  sentences, real computed perplexity (with and without smoothing, across
  n), a real Kneser-Ney continuation-count verification ("San Francisco"),
  generated sample text, use cases, and limitations & debates (long-range
  dependencies, curse of dimensionality, the smoothing-method zoo)
- `src/` — none needed; all code is inline in the notebook

## References

- Jurafsky, D. & Martin, J.H. *Speech and Language Processing* (3rd ed.
  draft), Chapter 3: N-gram Language Models.
- Kneser, R. & Ney, H. (1995). *Improved Backing-off for M-gram Language
  Modeling.* ICASSP, vol. 1, pp. 181–184.
- Chen, S.F. & Goodman, J. (1999). *An Empirical Study of Smoothing
  Techniques for Language Modeling.* Computer Speech & Language, 13(4),
  359–394.
- Shannon, C.E. (1948). *A Mathematical Theory of Communication.* Bell
  System Technical Journal, 27(3), 379–423.
- Shannon, C.E. (1951). *Prediction and Entropy of Printed English.* Bell
  System Technical Journal, 30(1), 50–64.
- Kucera, H. & Francis, W.N. (1967). *Computational Analysis of
  Present-Day American English.* Brown University Press (source of the
  Brown corpus, via `nltk.corpus.brown`).
