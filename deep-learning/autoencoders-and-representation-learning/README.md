# Autoencoders & Representation Learning

**Domain:** `deep-learning`
**Level:** Beginner / Intermediate
**Prerequisites:** basic Python, basic linear algebra, basic neural networks
(see `deep-learning/perceptron-and-backpropagation` if you haven't covered
feedforward networks and backpropagation yet)

## Summary

An autoencoder learns to compress data down to a small latent code and
reconstruct it back — the same "keep what matters, drop the rest" trick as
JPEG compression, except learned automatically from data rather than
hand-engineered. This tutorial starts with a linear PCA-based "simplest
possible autoencoder" on digit images, then formally derives the
encoder/decoder/bottleneck framework and the denoising-autoencoder variant
(train to recover a clean image from a corrupted one, which removes the
trivial identity-copying shortcut and produces more robust features). It
then trains a real vanilla autoencoder and a real denoising autoencoder in
PyTorch on MNIST, visualizes the learned latent space (showing digit classes
cluster even though no labels were used during training), and evaluates the
learned representation directly by training a linear classifier on top of
the frozen latent codes — reaching real double-digit accuracy on a task the
autoencoder was never trained for. The tutorial deliberately stays within
representation learning (compression, denoising, feature extraction) and
does not cover the VAE's generative/probabilistic framing, which belongs to
this repo's future `generative-ai` domain.

## Learning objectives

- Explain what an autoencoder's encoder, decoder, and bottleneck do, and why
  the bottleneck (not just "train a network to output its input") is what
  forces the network to learn a compressed, information-dense
  representation instead of a trivial identity mapping.
- Derive and justify the reconstruction loss (binary cross-entropy for
  [0,1]-normalized pixel intensities) and the denoising-autoencoder
  training objective, including the corruption process (additive Gaussian
  noise) and why it's often preferred to a vanilla autoencoder.
- Train a real vanilla autoencoder and a real denoising autoencoder on
  MNIST in PyTorch, and report real reconstruction loss numbers.
- Visualize a learned latent space (via PCA projection) colored by true
  class label, and explain why clustering there is evidence the network
  learned meaningful structure without ever seeing labels.
- Train a downstream linear classifier on frozen latent codes and evaluate
  it honestly, as a more direct test of representation quality than
  reconstruction loss alone.
- Name concrete failure modes of plain autoencoders (unstructured latent
  space, near-identity shortcuts) and where the field goes next (VAEs) to
  address them.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation

## References

- Vincent, Larochelle, Bengio & Manzagol (2008), *Extracting and Composing
  Robust Features with Denoising Autoencoders*, ICML.
- Hinton & Salakhutdinov (2006), *Reducing the Dimensionality of Data with
  Neural Networks*, Science.
- Goodfellow, Bengio & Courville (2016), *Deep Learning*, MIT Press, Ch. 14.
- Kingma & Welling (2013), *Auto-Encoding Variational Bayes*,
  arXiv:1312.6114 (forward-referenced; covered in this repo's
  `generative-ai` domain).
- LeCun, Cortes & Burges, *The MNIST Database of Handwritten Digits*.
- Pedregosa et al. (2011), *Scikit-learn: Machine Learning in Python*, JMLR.
