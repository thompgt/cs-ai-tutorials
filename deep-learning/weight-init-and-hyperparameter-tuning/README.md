# Weight Initialization & Hyperparameter Tuning

**Domain:** `deep-learning`
**Level:** Intermediate
**Prerequisites:** [The Perceptron & Backpropagation](../perceptron-and-backpropagation/README.md) (forward pass, backprop, gradient descent), basic Python, basic probability (mean/variance)

## Summary

Why you can't initialize a network's weights identically (e.g. all zero) —
demonstrated numerically on XOR before any formal math — and what scale of
randomness actually works. Derives the variance-scaling argument behind
Xavier/Glorot initialization (for symmetric activations like tanh/sigmoid)
and He/Kaiming initialization (for ReLU), then trains real 5-layer MLPs on
MNIST under zero/tiny-random/Xavier/He initialization to show, in real
numbers, which schemes actually train and which get stuck at a
majority-class baseline. Also covers hyperparameter tuning as a distinct
topic: the formal parameter-vs-hyperparameter distinction, grid search vs.
random search (citing Bergstra & Bengio's 2012 finding that random search
usually wins under a fixed budget), a brief conceptual note on Bayesian
optimization, and a real random search over learning rate x hidden width
on MNIST, visualized and reported with the actual best combination found.

## Learning objectives

- Explain and demonstrate why identical (e.g. all-zero) weight
  initialization prevents a network from learning anything beyond what a
  single linear unit could already do (the symmetry problem).
- Derive the variance-scaling argument for weight initialization, and
  state the Xavier/Glorot and He/Kaiming formulas and when each applies.
- Read activation-distribution histograms through a deep network's layers
  to diagnose vanishing/exploding activations from bad initialization.
- Define **parameter** vs. **hyperparameter** precisely, and implement and
  compare grid search vs. random search over a real hyperparameter space.
- Train and compare real MNIST classifiers under different init schemes,
  and run a real (CPU-tractable) random hyperparameter search.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation

## References

- Glorot, X., & Bengio, Y. (2010), *Understanding the difficulty of
  training deep feedforward neural networks*, AISTATS.
- He, K., Zhang, X., Ren, S., & Sun, J. (2015), *Delving Deep into
  Rectifiers*, ICCV.
- Bergstra, J., & Bengio, Y. (2012), *Random Search for Hyper-Parameter
  Optimization*, JMLR 13.
- Bergstra, J., Bardenet, R., Bengio, Y., & Kegl, B. (2011), *Algorithms
  for Hyper-Parameter Optimization*, NeurIPS.
- PyTorch documentation, `torch.nn.init`.
- LeCun, Cortes & Burges, *The MNIST Database of Handwritten Digits*.
