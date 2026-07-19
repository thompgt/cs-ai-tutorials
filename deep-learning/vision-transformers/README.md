# Vision Transformers (ViT)

**Domain:** `deep-learning`
**Level:** Intermediate
**Prerequisites:** basic Python and numpy; basic neural network familiarity
(see `perceptron-and-backpropagation`); helpful but not required — a skim of
`nlp/transformer-self-attention`, since this tutorial reuses (but does not
re-derive) its self-attention math

## Summary

Vision Transformers (ViT) apply the Transformer architecture — originally
built for text — to images, by chopping an image into a grid of patches and
treating each patch as a "visual word" in a sequence. This tutorial starts
with a real image sliced into patches using plain numpy (no deep learning),
then builds up the formal definition from Dosovitskiy et al. (2020): patch
embedding as a linear projection of flattened patches, the learnable
`[CLS]` token, learnable positional embeddings, and the full transformer
encoder forward pass (restating, but not re-deriving, the scaled
dot-product self-attention equation already covered in depth in
`nlp/transformer-self-attention`). It visualizes a real pretrained
`vit_b_16`'s class-token attention on a real photo (extracted via a forward
hook, since torchvision's built-in encoder discards attention weights by
default), builds a small ViT completely from scratch in PyTorch (custom
multi-head self-attention, not `nn.MultiheadAttention`) and trains it on a
real Fashion-MNIST subset, and runs the pretrained model on real images to
show its actual top-5 ImageNet predictions. It closes with where ViTs beat
CNNs in practice (large-data/foundation vision models) and where CNNs still
win (small-data, edge deployment), plus the field's still-unsettled
CNN-vs-ViT and hybrid-architecture debates.

## Learning objectives

- Explain, with a picture, how an image becomes a sequence of "visual word"
  tokens via patch embedding.
- State the formal ViT definitions precisely: patch embedding shapes, the
  `[CLS]` token, positional embeddings, and why attention needs them.
- Read a real pretrained ViT's attention weights and see, on a real photo,
  which patches the model actually looks at.
- Build a small Vision Transformer from scratch in PyTorch — patch
  embedding, hand-written multi-head self-attention, encoder blocks — and
  train it on real image data.
- Reason critically about when ViTs beat CNNs and when they don't, and
  where the field's hybrid-architecture debate currently stands.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation:
  - a real image sliced into a patch grid with numpy (the intuitive hook)
  - the formal ViT definitions (patch embedding, `[CLS]` token, positional
    embeddings, self-attention restated, full forward pass)
  - a real pretrained `vit_b_16`'s class-token attention map overlaid on a
    real photo
  - a from-scratch ViT (custom patch embedding, custom multi-head
    self-attention, transformer encoder blocks) trained on real
    Fashion-MNIST images, with real reported test accuracy
  - real pretrained-model inference (top-5 ImageNet predictions on two real
    photos)
  - use cases and a dedicated limitations & debates section

## References

- Dosovitskiy, A. et al. (2020). *An Image is Worth 16x16 Words:
  Transformers for Image Recognition at Scale.* ICLR 2021.
  [arXiv:2010.11929](https://arxiv.org/abs/2010.11929)
- Vaswani, A. et al. (2017). *Attention Is All You Need.* NeurIPS 2017.
- Abnar, S. & Zuidema, W. (2020). *Quantifying Attention Flow in
  Transformers.* ACL 2020.
- Jain, S. & Wallace, B. C. (2019). *Attention is not Explanation.* NAACL 2019.
- Liu, Z. et al. (2022). *A ConvNet for the 2020s* (ConvNeXt). CVPR 2022.
- Liu, Z. et al. (2021). *Swin Transformer: Hierarchical Vision Transformer
  using Shifted Windows.* ICCV 2021.
- Xiao, H., Rasul, K., & Vollgraf, R. (2017). *Fashion-MNIST: a Novel Image
  Dataset for Benchmarking Machine Learning Algorithms.*
