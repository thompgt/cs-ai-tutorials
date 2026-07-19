# Named Entity Recognition with Conditional Random Fields

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python; this domain's HMM-based part-of-speech
tagging tutorial is helpful context but not required

## Summary

Named Entity Recognition (NER) — finding people, organizations, and
locations in raw text — is a sequence-labeling task, exactly like
part-of-speech tagging. This tutorial introduces the **BIO tagging
scheme** (`B-PER`, `I-PER`, `B-LOC`, ..., `O`) and explains precisely why
it's needed: plain per-word entity-type tags can't distinguish two
separate one-word entities sitting next to each other from one multi-word
entity. It then introduces the **linear-chain Conditional Random Field
(CRF)** as a **discriminative** sequence model — a direct successor to
this domain's **generative** HMM tagger — deriving the full scoring
equation $P(\mathbf{y}\mid\mathbf{x}) = \frac{1}{Z(\mathbf{x})}
\exp\left(\sum_k \lambda_k \sum_i f_k(y_{i-1}, y_i, \mathbf{x}, i)\right)$
and explaining why its feature functions can use arbitrary, overlapping
signals from anywhere in the sentence — something an HMM's
current-word-only emission probability structurally cannot do. A real
per-token feature set (capitalization, suffixes, POS tags, and
neighboring-word context) is hand-engineered and used to train
`sklearn_crfsuite.CRF` on a real subset of the canonical **CoNLL-2003**
NER dataset, evaluated on the full real test split with token-level and
entity-level precision/recall/F1, and interpreted via the model's actual
learned feature weights.

## Learning objectives

- Explain why BIO tagging is needed, with a concrete example of two
  adjacent one-word entities vs. one multi-word entity.
- State the CRF scoring function from memory, define every symbol, and
  explain precisely why it lets a CRF use arbitrary, overlapping features
  of the whole observed sequence — in contrast to an HMM's emission
  probability, which only depends on the current word.
- Hand-engineer a real per-token NER feature set and train a real
  `sklearn-crfsuite` CRF on real CoNLL-2003 data.
- Read entity-level precision/recall/F1 and top learned feature weights
  to honestly evaluate what the model learned and where it fails.
- Explain why hand-crafted features motivate the shift to neural sequence
  taggers (BiLSTM-CRF, transformer-based NER).

## Contents

- `tutorial.ipynb` — plain-English hook (finding entities in a real
  sentence), BIO tagging worked example, the formal CRF derivation
  contrasted against the HMM's generative model, a feature-window
  visual, hand-crafted feature engineering, real CRF training and
  evaluation on CoNLL-2003 (token-level and entity-level F1), a
  learned-feature-weight visual per entity type, an F1-per-entity-type
  bar chart, real predicted-vs-true example sentences, use cases, and
  limitations & debates (feature transfer across domains/languages,
  inference cost, entity-boundary annotation disagreement)
- `src/` — none needed; all code is inline in the notebook

## References

- Lafferty, J., McCallum, A., Pereira, F. (2001). *Conditional Random
  Fields: Probabilistic Models for Segmenting and Labeling Sequence
  Data.* ICML 2001.
- Sang, E.F.T.K. & De Meulder, F. (2003). *Introduction to the CoNLL-2003
  Shared Task: Language-Independent Named Entity Recognition.* CoNLL 2003.
- Ramshaw, L.A. & Marcus, M.P. (1995). *Text Chunking Using
  Transformation-Based Learning.* Third ACL Workshop on Very Large
  Corpora.
- Lample, G., Ballesteros, M., Subramanian, S., Kawakami, K., Dyer, C.
  (2016). *Neural Architectures for Named Entity Recognition.*
  NAACL-HLT 2016.
- Jurafsky, D. & Martin, J.H. *Speech and Language Processing*, Chapters
  8 and 17.
- `sklearn-crfsuite` documentation:
  https://sklearn-crfsuite.readthedocs.io/
