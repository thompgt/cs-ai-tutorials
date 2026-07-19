# Optimization Algorithms for Deep Learning

**Domain:** `deep-learning`
**Level:** Intermediate
**Prerequisites:** basic Python, basic linear algebra (dot products, matrices),
basic calculus (gradients, partial derivatives); helpful but not required —
`deep-learning/perceptron-and-backpropagation` (backpropagation, gradient
descent basics)

## Summary

Gradient descent tells a network *which direction* to move its weights, but
not *how big a step* to take or *how to handle a loss surface shaped like a
narrow ravine* — and getting that wrong is why training can crawl or
oscillate for thousands of steps. This tutorial derives and implements, from
scratch in numpy on a visualizable 2D loss surface, the four optimizers that
actually show up in every deep learning training loop: vanilla SGD, SGD with
momentum, RMSprop, and Adam. It shows each one's trajectory converging (or
failing to) on the same elongated bowl via an overlaid contour plot, then
trains the same real PyTorch MLP on a real MNIST subset with all four
optimizers plus a learning-rate schedule, reporting actual test accuracies so
the toy-problem intuition connects to a measurable practical difference.

## Learning objectives

- Explain why plain SGD oscillates and converges slowly on ill-conditioned
  loss surfaces, using the "ball rolling down a narrow ravine" picture.
- Derive the update rules for SGD with momentum, RMSprop, and Adam, and state
  precisely what problem each new term (velocity, per-parameter adaptive
  learning rate, bias correction) solves.
- Implement all four optimizers from scratch in numpy and visualize their
  trajectories on the same 2D loss surface.
- Train an identical PyTorch MLP on real MNIST with each optimizer via
  `torch.optim`, compare training loss curves and final test accuracy, and
  compare a step-decay/cosine learning-rate schedule against a fixed rate.
- Know which optimizer practitioners reach for by default (Adam/AdamW), when
  SGD+momentum is still preferred, and the open debate around adaptive
  methods' generalization gap versus well-tuned SGD.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation

## References

- Sutskever, I., Martens, J., Dahl, G., & Hinton, G. (2013). *On the
  importance of initialization and momentum in deep learning.* ICML.
- Tieleman, T. & Hinton, G. (2012). *Lecture 6.5 - RMSProp*, COURSERA: Neural
  Networks for Machine Learning.
- Kingma, D. P. & Ba, J. (2015). *Adam: A Method for Stochastic
  Optimization.* ICLR.
- Loshchilov, I. & Hutter, F. (2019). *Decoupled Weight Decay Regularization*
  (AdamW). ICLR.
- Wilson, A. C., Roelofs, R., Stern, M., Srebro, N., & Recht, B. (2017). *The
  Marginal Value of Adaptive Gradient Methods in Machine Learning.* NeurIPS.
- Loshchilov, I. & Hutter, F. (2017). *SGDR: Stochastic Gradient Descent with
  Warm Restarts* (cosine annealing schedules). ICLR.
- Goodfellow, Bengio & Courville (2016), *Deep Learning*, MIT Press, Ch. 8
  (Optimization for Training Deep Models).
- LeCun, Cortes & Burges, *The MNIST Database of Handwritten Digits.*
