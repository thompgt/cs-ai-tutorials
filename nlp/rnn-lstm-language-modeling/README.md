# RNN / LSTM Language Modeling

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python; basic neural network familiarity helps but
isn't required; no prior NLP background needed

## Summary

N-gram language models (see this domain's **n-gram-language-models**
tutorial) can only ever condition on the last $n-1$ words, so they
structurally forget anything further back. This tutorial covers the
neural fix: a **recurrent neural network (RNN)** that maintains a hidden
state updated one token at a time, carrying information from arbitrarily
far back in the sequence. We derive, with the actual chain rule over
several timesteps, why the vanilla RNN's shared-weight-matrix recurrence
causes gradients to shrink exponentially with sequence length (the
**vanishing gradient problem**), then introduce the **LSTM**'s
forget/input/output gates and additive cell-state update as the fix that
gives gradients a direct, learnable path across many timesteps. A real
character-level LSTM (`torch.nn.LSTM`) is trained end-to-end in PyTorch on
Lewis Carroll's *Alice's Adventures in Wonderland* (NLTK's Gutenberg
corpus): real cross-entropy loss and perplexity dropping over 8 real
training epochs (loss 3.30 → 1.90, perplexity 27.2 → 6.7 in this run), a
held-out validation perplexity, and real generated text at low vs. high
sampling temperature, demonstrating the concrete conservative-vs-chaotic
generation tradeoff.

## Learning objectives

- Explain why a fixed-context-window model (n-grams) loses information
  that a running hidden state can, in principle, retain.
- Write down the vanilla RNN recurrence and derive why backpropagation
  through time causes vanishing gradients on long sequences.
- Write down the LSTM's gate and cell-state equations and explain why an
  additive cell-state update mitigates (not eliminates) vanishing
  gradients.
- Train a real character-level LSTM language model in PyTorch, evaluate it
  with perplexity, and generate text with temperature-controlled sampling.
- Explain why LSTMs' strictly sequential computation motivated the
  Transformer's shift to self-attention.

## Contents

- `tutorial.ipynb` — plain-English hook (framed as the neural fix for
  n-grams' fixed-window problem), a tiny hand-rolled NumPy RNN step
  demonstrating unbounded context, formal RNN/BPTT/vanishing-gradient
  derivation, formal LSTM gate equations with an additive-update gradient
  argument, a toy gradient-magnitude simulation (vanilla RNN vs. LSTM), a
  real character-level LSTM trained on Carroll's *Alice's Adventures in
  Wonderland*, real loss/perplexity curves, held-out perplexity, low- vs.
  high-temperature text generation, use cases, and limitations & debates
  (sequential bottleneck vs. Transformer parallelism, gating mitigates but
  doesn't eliminate long-range degradation, honest small-model caveats)
- `src/` — none needed; all code is inline in the notebook

## References

- Elman, J.L. (1990). *Finding Structure in Time.* Cognitive Science,
  14(2), 179–211.
- Hochreiter, S. & Schmidhuber, J. (1997). *Long Short-Term Memory.*
  Neural Computation, 9(8), 1735–1780.
- Bengio, Y., Simard, P., Frasconi, P. (1994). *Learning Long-Term
  Dependencies with Gradient Descent is Difficult.* IEEE Transactions on
  Neural Networks, 5(2), 157–166.
- Graves, A. (2013). *Generating Sequences With Recurrent Neural
  Networks.* arXiv:1308.0850.
- Karpathy, A. (2015). *The Unreasonable Effectiveness of Recurrent
  Neural Networks.* karpathy.github.io blog post.
- NLTK Project. `nltk.corpus.gutenberg` documentation (Carroll, L.,
  *Alice's Adventures in Wonderland*, 1865, public domain text).
- PyTorch documentation. `torch.nn.LSTM`, `torch.nn.Embedding`.
