# Part-of-Speech Tagging with Hidden Markov Models

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python; no prior NLP or probability background needed

## Summary

The word "book" is a noun in "I read a book" and a verb in "please book the
flight" — tagging it correctly requires looking at surrounding context, not
just the word itself, which makes part-of-speech (POS) tagging a **sequence
labeling problem** rather than a per-word classification problem. This
tutorial formalizes a **Hidden Markov Model (HMM)** for POS tagging (hidden
states = tags, observations = words, transition and emission probabilities,
and the two independence assumptions that make the model tractable), derives
the **Viterbi algorithm** and hand-traces its dynamic-programming table on a
tiny example, then trains transition and emission probabilities via MLE with
add-k smoothing on the real Penn Treebank corpus (3,914 human-annotated Wall
Street Journal sentences) and implements the Viterbi decoder from scratch.
The from-scratch tagger reaches **90.3% token accuracy** on held-out test
sentences; NLTK's pretrained averaged-perceptron tagger reaches **96.3%** on
the same sentences, and the tutorial honestly diagnoses the gap — mostly
capitalization information the HMM discards by lowercasing every word,
visible directly in the `NNP`/`NN` confusion that dominates the errors — and
connects that limitation forward to CRFs and neural sequence taggers.

## Learning objectives

- Explain why POS tagging is a sequence labeling problem, not a per-word
  classification problem, using a concrete lexical-ambiguity example.
- Define an HMM precisely for POS tagging: hidden states, observations,
  transition/emission probabilities, and the two independence assumptions.
- Derive the Viterbi recurrence, explain why it avoids exponential blowup,
  and hand-trace it step by step on a worked example.
- Train an HMM tagger from real annotated data with add-k smoothing,
  implement Viterbi decoding from scratch, and evaluate it honestly
  (overall accuracy, per-tag accuracy, confusion matrix) against a real
  pretrained baseline.

## Contents

- `tutorial.ipynb` — plain-English hook, formal HMM definition and Viterbi
  derivation with a hand-traced DP table, transition-matrix heatmaps (toy and
  real, learned from the Penn Treebank), a from-scratch MLE-trained HMM +
  Viterbi tagger evaluated on real held-out Penn Treebank sentences (overall
  accuracy, per-tag accuracy, confusion matrix of most-confused tag pairs),
  a head-to-head comparison against NLTK's pretrained `pos_tag`, use cases,
  and limitations & debates (independence assumptions, the CRF/NER
  connection, neural taggers)
- `src/` — none needed; all code is inline in the notebook

## References

- Rabiner, L.R. (1989). *A Tutorial on Hidden Markov Models and Selected
  Applications in Speech Recognition.* Proceedings of the IEEE, 77(2).
- Marcus, M.P., Marcinkiewicz, M.A., Santorini, B. (1993). *Building a
  Large Annotated Corpus of English: The Penn Treebank.* Computational
  Linguistics, 19(2).
- Viterbi, A.J. (1967). *Error Bounds for Convolutional Codes and an
  Asymptotically Optimum Decoding Algorithm.* IEEE Transactions on
  Information Theory, 13(2).
- Jurafsky, D. & Martin, J.H. *Speech and Language Processing*, Chapter 8
  (Part-of-Speech Tagging, Hidden Markov Models).
- NLTK Project. `nltk.corpus.treebank`, `nltk.pos_tag` documentation.
