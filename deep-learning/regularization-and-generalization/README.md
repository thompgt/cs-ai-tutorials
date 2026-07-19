# Regularization & Generalization in Deep Networks

**Domain:** `deep-learning`
**Level:** Beginner / Intermediate
**Prerequisites:** basic Python, basic linear algebra, gradient descent and
backpropagation (see the [perceptron-and-backpropagation](../perceptron-and-backpropagation/README.md)
tutorial), basic familiarity with PyTorch `nn.Module`

## Summary

Why does a neural network sometimes ace its training data but fail on new
examples — and what can be done about it? This tutorial opens with a tiny
polynomial-regression example that makes overfitting visible in ten lines
of numpy, then derives three of the most widely used regularizers precisely:
**L2 weight decay** (with its Bayesian MAP interpretation), **dropout**
(Srivastava et al., 2014, with exact train-vs-eval equations), and **batch
normalization** (Ioffe & Szegedy, 2015, including the internal-covariate-shift
vs. smoother-loss-landscape debate), plus **data augmentation** as a way of
regularizing the data itself. The implementation trains the same small CNN
architecture four ways — no regularization, + weight decay, + dropout, and
+ batch norm/augmentation combined — on a deliberately small 1,500-image
Fashion-MNIST subset, and reports the real train/test accuracy gap for each
variant, showing how (and how much) each regularizer actually closes it.

## Learning objectives

- Recognize overfitting from train vs. test error curves and explain it in
  terms of model capacity vs. data, using a from-scratch polynomial example.
- Derive L2 weight decay's gradient-shrinkage effect and its equivalence to
  MAP estimation under a Gaussian weight prior.
- State dropout's exact train-time (inverted scaling) and eval-time
  equations, and explain why it approximates ensembling many sub-networks.
- State batch normalization's exact formula (including running statistics
  used at eval time), and describe the open debate over why it helps.
- Explain data augmentation as regularizing the effective training
  distribution rather than the model or optimizer.
- Train and compare four regularization variants of the same CNN on a real,
  data-starved image classification task, and interpret the resulting
  train/test accuracy gaps honestly, including when they don't rank in the
  expected order.
- Know which regularizers practitioners default to for which architectures,
  and identify open questions (double descent, implicit regularization of
  SGD) about why over-parameterized networks generalize at all.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation

## References

- Srivastava, Hinton, Krizhevsky, Sutskever & Salakhutdinov (2014),
  *Dropout: A Simple Way to Prevent Neural Networks from Overfitting*,
  JMLR.
- Ioffe & Szegedy (2015), *Batch Normalization: Accelerating Deep Network
  Training by Reducing Internal Covariate Shift*, ICML.
- Santurkar, Tsipras, Ilyas & Madry (2018), *How Does Batch Normalization
  Help Optimization?*, NeurIPS.
- Li, Chen, Hu & Yang (2019), *Understanding the Disharmony between Dropout
  and Batch Normalization by Variance Shift*, CVPR.
- Loshchilov & Hutter (2019), *Decoupled Weight Decay Regularization*, ICLR
  (the AdamW paper).
- Belkin, Hsu, Ma & Mandal (2019), *Reconciling Modern Machine-Learning
  Practice and the Classical Bias-Variance Trade-off*, PNAS (double
  descent).
- Xiao, Rasul & Vollgraf (2017), *Fashion-MNIST: a Novel Image Dataset for
  Benchmarking Machine Learning Algorithms*.
- Goodfellow, Bengio & Courville (2016), *Deep Learning*, MIT Press, Ch. 7
  (Regularization for Deep Learning).
