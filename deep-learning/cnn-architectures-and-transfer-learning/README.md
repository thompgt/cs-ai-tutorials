# Modern CNN Architectures & Transfer Learning

**Domain:** `deep-learning`
**Level:** Intermediate
**Prerequisites:** what a convolution and pooling layer compute (see
`convolutional-neural-networks`), the backpropagation / vanishing-gradient
material from `perceptron-and-backpropagation`, basic PyTorch (tensors,
`nn.Module`, autograd)

## Summary

Why stacking more convolutional layers can make a network's training error
*worse*, not better (the degradation problem), and the residual/skip
connection (He et al., 2015, ResNet) that fixes it by giving every block an
identity shortcut and an unimpeded gradient path back to earlier layers.
Covers the residual block equation and its gradient-flow argument (tied
explicitly back to the vanishing-gradient discussion in
`perceptron-and-backpropagation`), VGG's small-filter depth recipe, and the
general depth-vs-width tradeoff. Demonstrates the degradation problem and
its fix with a real training-loss comparison (plain vs. residual CNNs of
the same depth) on real Oxford-IIIT Pet images. The core implementation is
real transfer learning: an ImageNet-pretrained `resnet18` (frozen backbone
+ new head) vs. a small CNN trained from scratch, both evaluated on the
same small, real, held-out image set — a real measured 24.0% (from scratch)
vs. 93.3% (transfer learning) test-accuracy gap on this run.

## Learning objectives

- Explain the degradation problem and why it's an optimization failure of
  plain deep networks, not overfitting.
- Derive why a residual connection ($y = F(x, \{W_i\}) + x$) improves
  gradient flow during backpropagation, and connect it to the
  vanishing-gradient problem covered in the perceptron tutorial.
- Describe VGG's and ResNet's core architectural ideas and the general
  depth-vs-width tradeoff.
- Load a real pretrained `torchvision.models` CNN and apply transfer
  learning (frozen-backbone feature extraction) to a new, small dataset.
- Compare from-scratch training vs. transfer learning with real, measured
  test accuracy on the same data, and reason about when to freeze vs.
  fine-tune a pretrained backbone.
- Identify transfer learning's domain-gap failure mode and the real compute
  cost that makes it the practical default outside large labs.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation

## References

- He, K., Zhang, X., Ren, S., & Sun, J. (2015). *Deep Residual Learning for
  Image Recognition.* arXiv:1512.03385.
- Simonyan, K., & Zisserman, A. (2014). *Very Deep Convolutional Networks
  for Large-Scale Image Recognition.* arXiv:1409.1556.
- Szegedy, C. et al. (2014). *Going Deeper with Convolutions.*
  arXiv:1409.4842.
- Deng, J., Dong, W., Socher, R., Li, L.-J., Li, K., & Fei-Fei, L. (2009).
  *ImageNet: A Large-Scale Hierarchical Image Database.* CVPR.
- Raghu, M., Zhang, C., Kleinberg, J., & Bengio, S. (2019). *Transfusion:
  Understanding Transfer Learning for Medical Imaging.* NeurIPS.
- Parkhi, O. M., Vedaldi, A., Zisserman, A., & Jawahar, C. V. (2012). *Cats
  and Dogs.* CVPR. (Oxford-IIIT Pet dataset)
- `torchvision.models` documentation,
  [pytorch.org/vision/stable/models.html](https://pytorch.org/vision/stable/models.html)
