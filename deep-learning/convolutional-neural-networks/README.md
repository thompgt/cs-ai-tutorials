# Convolutional Neural Networks

**Domain:** `deep-learning`
**Level:** Beginner / Intermediate
**Prerequisites:** the perceptron & backpropagation tutorial in this domain
(what a neuron/layer computes, gradient descent), basic Python, basic linear
algebra.

## Summary

Builds on the perceptron/backpropagation tutorial by explaining why a
fully-connected network is a poor fit for images, and how convolution fixes
it. Starts with a from-scratch numpy 2D convolution using a hand-crafted
Sobel-style edge kernel applied to a real Fashion-MNIST image, then derives
the formal definitions used in practice: cross-correlation vs. true
convolution, stride/padding and the output-size formula, max/average
pooling and the (partial) translation invariance it grants, and the
parameter-sharing argument for why conv layers need far fewer weights than
an equivalent dense layer — backed by an explicit numeric comparison.
Trains a real 3-conv-layer CNN in PyTorch on Fashion-MNIST and compares it
directly, in real test accuracy and real parameter counts, against an MLP
baseline on the same data (CNN: 86.40% accuracy with 60,874 parameters;
MLP: 84.48% accuracy with 101,770 parameters). Visualizes the trained CNN's
learned first-layer filters and intermediate feature maps on a real input
image. Closes with real-world use cases (classification, detection/
segmentation backbones, an aside on 1D convolution for sequences) and a
critical look at CNN limitations — adversarial sensitivity, the limits of
pooling's translation invariance, and the ongoing CNN-vs-Vision-Transformer
debate.

## Learning objectives

- Explain, intuitively and mathematically, what a 2D convolution computes
  and why it is a natural fit for image data.
- Derive the output-size formula for a convolution given stride and
  padding, and explain what max/average pooling do and why they grant
  (partial) translation invariance.
- Explain and numerically verify why convolutional layers have far fewer
  parameters than a fully-connected layer over the same input.
- Build, train, and evaluate a real CNN in PyTorch on real image data, and
  compare it numerically — accuracy *and* parameter count — against an MLP
  baseline on the same data.
- Visualize a trained CNN's learned filters and intermediate feature maps.
- Describe where CNNs are used in practice, and their known limitations.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation

## References

- LeCun, Bottou, Bengio & Haffner (1998), *Gradient-based learning applied
  to document recognition*, Proceedings of the IEEE (the original CNN /
  LeNet-5 paper).
- Krizhevsky, Sutskever & Hinton (2012), *ImageNet classification with deep
  convolutional neural networks* (AlexNet), NeurIPS.
- Xiao, Rasul & Vollgraf (2017), *Fashion-MNIST: a novel image dataset for
  benchmarking machine learning algorithms*, arXiv:1708.07747.
- Szegedy et al. (2013), *Intriguing properties of neural networks*,
  arXiv:1312.6199 (adversarial examples).
- Azulay & Weiss (2019), *Why do deep convolutional networks generalize so
  poorly to small image transformations?*, JMLR, arXiv:1805.12177.
- Dosovitskiy et al. (2020), *An Image is Worth 16x16 Words: Transformers
  for Image Recognition at Scale* (ViT), arXiv:2010.11929.
- Goodfellow, Bengio & Courville (2016), *Deep Learning*, MIT Press,
  Chapter 9 (Convolutional Networks).
