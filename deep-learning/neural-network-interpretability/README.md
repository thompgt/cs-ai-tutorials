# Neural Network Interpretability: Saliency Maps & Grad-CAM

**Domain:** `deep-learning`
**Level:** Intermediate
**Prerequisites:** the `perceptron-and-backpropagation` tutorial in this
domain (what backpropagation computes and why), basic familiarity with
convolutional neural networks (a conv layer produces a stack of 2D feature
maps), basic Python/PyTorch.

## Summary

A CNN can be highly accurate for entirely the wrong reason — the famous
"husky classified as wolf because of snow in the background" failure from
the LIME paper is a real, documented example. This tutorial covers two
gradient-based tools for asking "where in the image was the model actually
looking": **vanilla gradient saliency** (Simonyan et al., 2013), the raw
gradient of the predicted class score with respect to input pixels, and
**Grad-CAM** (Selvaraju et al., 2017), which computes class-specific
importance weights for a convolutional layer's feature maps and combines
them into a coarser but more semantically meaningful heatmap. Both are
derived precisely, implemented from scratch with PyTorch forward/backward
hooks, and validated against `captum`'s reference implementations (pixel-wise
correlation of 1.0000 on a real ImageNet-pretrained ResNet-18). The
notebook demonstrates both methods on multiple real images, includes a
class-specificity sanity check (the same image, correct class vs. an
unrelated class, showing the heatmap moves), and closes with an honest
discussion of the "Sanity Checks for Saliency Maps" critique (Adebayo et
al., 2018) and Grad-CAM's resolution limitations.

## Learning objectives

- Explain what a saliency map and a Grad-CAM heatmap each show, and how
  they differ.
- Derive vanilla gradient saliency and Grad-CAM precisely, including why
  Grad-CAM applies ReLU and why it targets a late (not first, not final)
  convolutional layer.
- Implement both methods from scratch using PyTorch forward/backward hooks,
  and validate the implementation against `captum`.
- Use these tools to detect spurious correlations / dataset bias and debug
  misclassifications on a real pretrained ImageNet model.
- Explain the real limitations of saliency methods, including the
  "Sanity Checks for Saliency Maps" critique, and why these tools are
  correlational, not causal, explanations.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation. Uses a pretrained
  `torchvision.models.resnet18` (ImageNet weights) on real sample images
  downloaded at run time from torchvision's own example gallery.

## References

- Simonyan, Vedaldi & Zisserman (2013), *Deep Inside Convolutional
  Networks: Visualising Image Classification Models and Saliency Maps*,
  arXiv:1312.6034.
- Selvaraju et al. (2017), *Grad-CAM: Visual Explanations from Deep
  Networks via Gradient-based Localization*, ICCV 2017 / IJCV,
  arXiv:1610.02391.
- Ribeiro, Singh & Guestrin (2016), *"Why Should I Trust You?": Explaining
  the Predictions of Any Classifier*, KDD 2016 (the husky/wolf snow example;
  also the paper introducing LIME, covered in this repo's
  `responsible-data-science` domain).
- Adebayo et al. (2018), *Sanity Checks for Saliency Maps*, NeurIPS 2018,
  arXiv:1810.03292.
- Kokhlikyan et al. (2020), *Captum: A unified and generic model
  interpretability library for PyTorch*, [captum.ai](https://captum.ai/).
- He, Zhang, Ren & Sun (2016), *Deep Residual Learning for Image
  Recognition*, CVPR 2016 (ResNet).
- Deng et al. (2009), *ImageNet: A Large-Scale Hierarchical Image
  Database*, CVPR 2009.
