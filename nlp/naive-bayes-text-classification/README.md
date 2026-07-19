# Naive Bayes Text Classification

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python, Bayes' theorem helpful but not required (derived from scratch)

## Summary

Naive Bayes is one of the oldest, cheapest, and most surprisingly effective
algorithms in text classification — the original engine behind spam
filters and still a standard baseline for sentiment analysis. This tutorial
derives the classifier from Bayes' theorem, states the conditional
independence ("naive") assumption explicitly as a known-false simplification,
derives the log-space decision rule (and shows numerical underflow happening
for real without it), and derives Laplace (add-one) smoothing by first
showing, on a toy example, how a single unseen word can zero out an entire
class probability without it. The classifier is then trained for real on
`nltk.corpus.movie_reviews` (the Pang & Lee 2,000-review sentiment polarity
dataset) both with `scikit-learn`'s `MultinomialNB` and as a from-scratch
implementation built directly from the derivation, with real accuracy,
precision, recall, a confusion matrix, and a most-informative-words plot
showing genuine sentiment vocabulary the model learned.

## Learning objectives

- Derive the Naive Bayes classification rule from Bayes' theorem and state
  precisely what the conditional independence assumption is and why it's
  known to be false.
- Explain why practical implementations classify in log-space rather than
  multiplying raw probabilities.
- Derive Laplace (add-one) smoothing and demonstrate concretely why skipping
  it lets a single unseen word veto an entire class.
- Train and evaluate `MultinomialNB` on real movie review data, and confirm
  a from-scratch implementation of the same math produces matching
  predictions.
- Read off which words a trained classifier finds most diagnostic per class,
  and know why naively ranking by raw log-likelihood ratio surfaces noisy
  proper nouns instead of real sentiment vocabulary.
- Know where Naive Bayes is a strong choice (speed, simplicity), where it's
  miscalibrated, and what practitioners reach for instead (logistic
  regression, linear SVM, Platt scaling).

## Contents

- `tutorial.ipynb` — plain-English hook and toy 4-document example, the
  Bayes'-rule derivation, log-space and Laplace-smoothing derivations with
  concrete underflow/zero-probability demonstrations, a full real-data
  pipeline on `nltk.corpus.movie_reviews` (train/test split, `CountVectorizer`
  bag-of-words, `sklearn.naive_bayes.MultinomialNB`, a from-scratch
  reimplementation that matches sklearn's predictions), a confusion matrix
  heatmap, a most-informative-words-per-class bar chart, use cases, and
  limitations & debates (the independence assumption, bag-of-words
  word-order blindness, probability miscalibration, and a contrast against
  logistic regression / linear SVM)
- `src/` — none needed; all code is inline in the notebook

## References

- Pang, B., Lee, L. (2004). *A Sentimental Education: Sentiment Analysis
  Using Subjectivity Summarization Based on Minimum Cuts.* ACL 2004.
- Pang, B., Lee, L., Vaithyanathan, S. (2002). *Thumbs up? Sentiment
  Classification using Machine Learning Techniques.* EMNLP 2002.
- McCallum, A., Nigam, K. (1998). *A Comparison of Event Models for Naive
  Bayes Text Classification.* AAAI-98 Workshop on Learning for Text
  Categorization.
- Domingos, P., Pazzani, M. (1997). *On the Optimality of the Simple
  Bayesian Classifier under Zero-One Loss.* Machine Learning, 29(2-3).
- Jurafsky, D., Martin, J.H. *Speech and Language Processing*, Chapter 4:
  Naive Bayes, Text Classification, and Sentiment.
- Graham, P. (2002). *A Plan for Spam.*
- NLTK Project. `nltk.corpus.movie_reviews`,
  `sklearn.naive_bayes.MultinomialNB` documentation.
