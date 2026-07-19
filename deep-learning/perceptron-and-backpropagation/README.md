# The Perceptron & Backpropagation

**Domain:** `deep-learning`
**Level:** Beginner
**Prerequisites:** basic Python, basic linear algebra (dot products, matrices), basic calculus (derivatives, chain rule)

## Summary

The foundational tutorial for the deep-learning domain: what a single neuron
computes, why stacking neurons into layers is necessary (via the XOR
problem, unsolvable by any single linear unit), and a from-scratch
derivation and numpy implementation of backpropagation with no autodiff.
Verifies the hand-derived gradients with a numerical gradient check, then
scales the same architecture to a real handwritten-digit classifier on
MNIST — reaching ~94% real test accuracy — and compares it directly against
an equivalent PyTorch model to show autograd is doing the same chain-rule
bookkeeping automatically.

## Learning objectives

- Understand what a single neuron computes and why layering neurons makes a
  network more expressive than any single neuron (the XOR problem).
- Derive backpropagation from the chain rule for a small network, by hand.
- Implement a feedforward network and backpropagation from scratch in numpy,
  and verify the gradients with a numerical gradient check.
- Train and evaluate a real MNIST digit classifier, and compare a
  from-scratch implementation against an equivalent PyTorch model.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation

## References

- Rumelhart, Hinton & Williams (1986), *Learning representations by
  back-propagating errors*, Nature.
- Nielsen, M., *Neural Networks and Deep Learning*,
  neuralnetworksanddeeplearning.com
- Goodfellow, Bengio & Courville (2016), *Deep Learning*, MIT Press, Ch. 6/8.
- LeCun, Cortes & Burges, *The MNIST Database of Handwritten Digits*.
- Cybenko (1989), *Approximation by superpositions of a sigmoidal function*.
