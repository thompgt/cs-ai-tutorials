# The Transformer & Self-Attention

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate-to-advanced rigor
**Prerequisites:** Basic Python; basic neural network familiarity (embeddings,
linear layers) helps but isn't required; no prior attention/Transformer
background needed

## Summary

The `rnn-lstm-language-modeling` and `seq2seq-attention-machine-translation`
tutorials in this domain both hit the same wall: RNNs process a sequence
one token at a time, which is an inherent sequential bottleneck, and even
seq2seq's cross-attention fix still runs on top of a sequential RNN
encoder. This tutorial covers **the Transformer** (Vaswani et al., 2017),
centered on **self-attention** — the same attention idea generalized so
every position in a *single* sequence attends to every other position in
that sequence, computed in parallel rather than step by step. It derives
**scaled dot-product attention** precisely (including *why* the
$1/\sqrt{d_k}$ scaling term is mathematically necessary, shown with a real
numeric softmax-saturation example), derives **multi-head attention**, and
explains why self-attention needs explicit **positional encoding** since it
has no inherent notion of token order (demonstrated concretely with a
permutation experiment). Scaled dot-product and multi-head attention are
then implemented **from scratch** in PyTorch and run on real spaCy word
embeddings, and a real pretrained **DistilBERT** model is loaded via
HuggingFace `transformers` to extract and visualize its actual attention
weights on a Winograd-schema-style coreference sentence ("The trophy
doesn't fit in the suitcase because it is too big").

## Learning objectives

- Explain why self-attention is parallel where RNN-based sequence models
  are inherently sequential.
- Derive scaled dot-product attention and multi-head attention, including
  why the $1/\sqrt{d_k}$ scaling factor is needed to keep softmax gradients
  usable.
- Explain why self-attention has no built-in notion of token order, and how
  sinusoidal positional encoding fixes that.
- Implement multi-head self-attention from scratch in PyTorch.
- Load a real pretrained Transformer and extract/visualize its actual
  attention weights, and reason critically about what those weights do and
  don't tell you.

## Contents

- `tutorial.ipynb` — plain-English hook framed against this domain's
  RNN/seq2seq sibling tutorials, formal derivation of scaled dot-product
  and multi-head attention with a numeric softmax-saturation demonstration,
  sinusoidal positional encoding with a permutation-invariance experiment,
  from-scratch PyTorch multi-head self-attention run on real spaCy word
  embeddings (attention heatmap), a real pretrained DistilBERT model's
  attention weights extracted and visualized on a coreference sentence
  (second attention heatmap), use cases (BERT/GPT/encoder-decoder
  Transformers, vision/audio Transformers), and limitations & debates
  ($O(n^2)$ attention cost and efficient-attention variants, the "attention
  is not explanation" debate, evolving positional-encoding design)
- `src/` — none needed; all code is inline in the notebook

## References

- Vaswani, A. et al. (2017). *Attention Is All You Need.* NeurIPS 2017.
- Devlin, J., Chang, M.W., Lee, K., Toutanova, K. (2019). *BERT:
  Pre-training of Deep Bidirectional Transformers for Language
  Understanding.* NAACL 2019.
- Jain, S. & Wallace, B.C. (2019). *Attention is not Explanation.* NAACL
  2019.
- Wolf, T., Debut, L., Sanh, V., et al. (2020). *Transformers:
  State-of-the-Art Natural Language Processing.* EMNLP 2020 (System
  Demonstrations).
- Sanh, V., Debut, L., Chaumond, J., Wolf, T. (2019). *DistilBERT, a
  distilled version of BERT.* EMC^2 Workshop, NeurIPS 2019.
- Su, J., Lu, Y., Pan, S., Wen, B., Liu, Y. (2021). *RoFormer: Enhanced
  Transformer with Rotary Position Embedding* (RoPE).
- Beltagy, I., Peters, M.E., Cohan, A. (2020). *Longformer: The
  Long-Document Transformer.*
