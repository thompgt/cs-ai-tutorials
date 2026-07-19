# Sequence-to-Sequence Models with Attention (Neural Machine Translation)

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python; this domain's RNN/LSTM language-modeling
tutorial (same recurrent building block, used here for encoder-decoder
sequence transduction instead of next-token prediction)

## Summary

Translation can't be done the way POS tagging or NER (this domain's
sequence-labeling tutorials) are done, tagging each input token in place,
because the output has a different length and different word order than
the input. This tutorial builds the **encoder-decoder architecture**
(Sutskever et al., 2014) that fixes that: one recurrent network reads and
compresses the source sentence, a second one generates the target sentence
token by token. It then derives, precisely, why compressing an entire
sentence into one fixed-size vector is a real bottleneck (Cho et al.,
2014's original degrades-with-length observation) and how the **attention
mechanism** (Bahdanau et al., 2015) fixes it: at every decoder step, score
every encoder position, normalize via softmax, and form a context vector
as a weighted sum — letting the decoder look at different source words for
different output words. A real encoder-decoder-with-attention model is
then trained from scratch in PyTorch on real English-French sentence pairs
(Hugging Face's `opus_books`), with a real training loss curve, real
(honestly rough, small-model) translations of held-out sentences, and a
real extracted attention-weight heatmap showing the model's learned
source-to-target alignment.

## Learning objectives

- Explain why machine translation needs an encoder-decoder architecture
  rather than a sequence tagger, and implement the basic version in
  PyTorch.
- State precisely why the fixed-size context vector is a bottleneck, and
  derive the Bahdanau attention mechanism (alignment scores -> softmax ->
  weighted-sum context vector) that fixes it.
- Train a real encoder-decoder-with-attention NMT model with teacher
  forcing, and extract and interpret real attention weights for a
  translated example.
- Explain how this attention mechanism directly foreshadows the
  Transformer's self-attention (this domain's next tutorial), and name the
  real sequential-computation / evaluation-metric tradeoffs this
  architecture still has.

## Contents

- `tutorial.ipynb` — plain-English hook (why translation isn't sequence
  tagging), a shape-only encoder demo, the formal encoder-decoder and
  Bahdanau-attention derivations, a toy attention-heatmap intuition
  build, a real PyTorch encoder-decoder-with-attention model trained on
  a filtered short-sentence subset of `Helsinki-NLP/opus_books` (en-fr),
  a real training loss curve, real held-out translations, a real
  extracted attention-weight heatmap, use cases, and limitations &
  debates (sequential-computation bottleneck, attention's own O(n) cost
  vs. the Transformer's O(n^2) self-attention, small-model honesty, and
  BLEU-metric criticism)
- `src/` — none needed; all code is inline in the notebook

## References

- Sutskever, I., Vinyals, O., Le, Q.V. (2014). *Sequence to Sequence
  Learning with Neural Networks.* NeurIPS 2014.
- Cho, K., van Merrienboer, B., Bahdanau, D., Bengio, Y. (2014). *On the
  Properties of Neural Machine Translation: Encoder-Decoder Approaches.*
  SSST-8.
- Bahdanau, D., Cho, K., Bengio, Y. (2015). *Neural Machine Translation by
  Jointly Learning to Align and Translate.* ICLR 2015.
- Luong, M.T., Pham, H., Manning, C.D. (2015). *Effective Approaches to
  Attention-based Neural Machine Translation.* EMNLP 2015.
- Vaswani, A., Shazeer, N., Parmar, N., et al. (2017). *Attention Is All
  You Need.* NeurIPS 2017.
- Tiedemann, J. (2012). *Parallel Data, Tools and Interfaces in OPUS.*
  LREC 2012.
- Wu, Y., Schuster, M., Chen, Z., et al. (2016). *Google's Neural Machine
  Translation System: Bridging the Gap between Human and Machine
  Translation.*
- Papineni, K., Roukos, S., Ward, T., Zhu, W.J. (2002). *BLEU: a Method
  for Automatic Evaluation of Machine Translation.* ACL 2002.
