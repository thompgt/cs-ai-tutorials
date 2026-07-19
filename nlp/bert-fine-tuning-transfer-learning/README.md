# Transfer Learning & Fine-Tuning BERT

**Domain:** `nlp`
**Level:** Beginner-friendly intro, advanced rigor (domain capstone)
**Prerequisites:** Basic Python; this domain's `bag-of-words-and-tfidf`,
`word-embeddings`, and `transformer-self-attention` tutorials are
referenced throughout and recommended first, though not strictly required.

## Summary

This is the NLP domain's capstone tutorial: it explains and demonstrates
**transfer learning** via **fine-tuning BERT**. Instead of training a text
classifier from scratch on a small labeled dataset, you start from
`distilbert-base-uncased` — a model already pretrained on hundreds of
millions of words via **masked language modeling (MLM)**, which is what
makes BERT genuinely *bidirectional* in contrast to GPT-style causal
language models — and then **fine-tune** it (continue training, with a
small classification head on the `[CLS]` token, at a low learning rate for
a few epochs) on a specific labeled task. The tutorial builds and
honestly compares **three real models** on the same real subset of the
Stanford Sentiment Treebank v2 (SST-2): a classical TF-IDF + Logistic
Regression baseline, a zero-shot BERT with an untrained (randomly
initialized) classification head, and a genuinely fine-tuned
`distilbert-base-uncased`. All three are evaluated on the same held-out
subset and every reported number is measured from a real run, not assumed
— in this run, fine-tuned BERT (0.820 accuracy) clearly outperformed both
the TF-IDF baseline (0.545) and the untrained zero-shot head (0.420, near
chance), even under a tight CPU fine-tuning budget (400 training examples,
2 epochs, ~4 minutes).

## Learning objectives

- Explain transfer learning and fine-tuning in plain English, and why
  starting from a pretrained model beats training from scratch when
  labeled data is scarce.
- State precisely what BERT's masked language modeling pretraining
  objective is, and why it makes BERT bidirectional in contrast to
  GPT-style causal language modeling.
- State the fine-tuning setup for classification (the `[CLS]` token's
  final hidden state through a linear head, whole model updated via
  gradient descent) and explain why the fine-tuning learning rate must be
  much smaller than from-scratch training, to avoid **catastrophic
  forgetting**.
- Build and honestly compare three real classifiers — TF-IDF+LR, zero-shot
  BERT, and fine-tuned BERT — on the same real SST-2 data, and interpret
  real accuracy numbers rather than assumed ones.
- Know the real practical tradeoffs of fine-tuning full BERT-family models
  (compute/memory cost, catastrophic forgetting risk, inherited bias) and
  name **parameter-efficient fine-tuning** (LoRA, adapters) as the modern
  practitioner's mitigation.

## Contents

- `tutorial.ipynb` — plain-English hook, formal MLM/bidirectionality and
  fine-tuning derivation, a pretrain-vs-fine-tune pipeline diagram, a real
  three-way model comparison on real SST-2 data (TF-IDF+LR baseline,
  untrained zero-shot BERT head, and a real fine-tuned
  `distilbert-base-uncased` with a manual PyTorch training loop), accuracy
  and training-loss visuals, use cases connecting to modern instruction-tuned
  LLMs, and limitations & debates (catastrophic forgetting, compute cost,
  PEFT/LoRA, inherited bias, scale-vs-efficiency debate)
- `src/` — none needed; all code is inline in the notebook

## References

- Devlin, J., Chang, M.W., Lee, K., Toutanova, K. (2019). *BERT:
  Pre-training of Deep Bidirectional Transformers for Language
  Understanding.* NAACL 2019.
- Sanh, V., Debut, L., Chaumond, J., Wolf, T. (2019). *DistilBERT, a
  distilled version of BERT: smaller, faster, cheaper and lighter.* NeurIPS
  EMC² Workshop 2019.
- Socher, R., Perelygin, A., Wu, J., Chuang, J., Manning, C.D., Ng, A.,
  Potts, C. (2013). *Recursive Deep Models for Semantic Compositionality
  Over a Sentiment Treebank.* EMNLP 2013.
- Howard, J. & Ruder, S. (2018). *Universal Language Model Fine-tuning for
  Text Classification (ULMFiT).* ACL 2018.
- Hu, E.J., Shen, Y., Wallis, P., Allen-Zhu, Z., Li, Y., Wang, S., Wang,
  L., Chen, W. (2021). *LoRA: Low-Rank Adaptation of Large Language
  Models.*
- Wolf, T. et al. (2020). *Transformers: State-of-the-Art Natural Language
  Processing.* EMNLP 2020 (System Demonstrations).
- Liu, Y. et al. (2019). *RoBERTa: A Robustly Optimized BERT Pretraining
  Approach.*
