# Tokenization & Text Preprocessing

**Domain:** `nlp`
**Level:** Beginner-friendly intro, intermediate rigor
**Prerequisites:** Basic Python; no prior NLP background needed

## Summary

Every NLP model — bag-of-words, n-gram language models, embeddings, RNNs,
transformers — operates on tokens, not raw text, so how you split text into
tokens silently caps what everything downstream can learn. This tutorial
shows naive whitespace splitting failing on a real sentence, introduces
rule-based tokenization, then formalizes **stemming** (the crude,
rule-based Porter algorithm) versus **lemmatization** (dictionary + POS-aware
lookup), and derives **Byte-Pair Encoding (BPE)** — the subword tokenization
algorithm behind GPT, BERT's WordPiece, and LLaMA's SentencePiece — from
scratch. BPE is trained for real on Jane Austen's *Emma* and then applied to
words that provably never appeared in an 1815 novel (`"tokenization"`,
`"blockchain"`, `"wifi"`), demonstrating concretely why subword tokenization
eliminates the out-of-vocabulary problem that whole-word tokenizers can't
escape.

## Learning objectives

- Explain why naive whitespace splitting fails, and what a rule-based
  tokenizer fixes.
- State precisely what stemming and lemmatization each do, and why they can
  produce very different (and differently correct) outputs.
- Derive the BPE training algorithm (merge-the-most-frequent-adjacent-pair)
  and implement it from scratch.
- Explain why subword tokenization can tokenize literally any input string,
  and why that matters for every modern LLM tokenizer.

## Contents

- `tutorial.ipynb` — plain-English hook, a from-scratch BPE implementation
  trained on real text (Austen's *Emma*, via NLTK's Gutenberg corpus),
  stemming vs. lemmatization comparison on real inflected words, BPE
  vocabulary-growth and token-length visuals, OOV handling demo on unseen
  modern words, use cases, and limitations & debates (tokenizer bias across
  languages, over/under-stemming)
- `src/` — none needed; all code is inline in the notebook

## References

- Porter, M.F. (1980). *An Algorithm for Suffix Stripping.* Program 14(3).
- Sennrich, R., Haddow, B., Birch, A. (2016). *Neural Machine Translation
  of Rare Words with Subword Units.* ACL 2016.
- Devlin, J., Chang, M.W., Lee, K., Toutanova, K. (2019). *BERT:
  Pre-training of Deep Bidirectional Transformers for Language
  Understanding.* NAACL 2019.
- Kudo, T. & Richardson, J. (2018). *SentencePiece.* EMNLP 2018.
- Manning, C.D., Raghavan, P., Schütze, H. (2008). *Introduction to
  Information Retrieval*, Chapter 2. Cambridge University Press.
- Ahia, O. et al. (2023). *Do All Languages Cost the Same? Tokenization in
  the Era of Commercial Language Models.* EMNLP 2023.
- NLTK Project. `nltk.tokenize`, `nltk.stem` documentation.
