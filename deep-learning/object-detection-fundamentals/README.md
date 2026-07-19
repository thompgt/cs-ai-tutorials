# Object Detection Fundamentals

**Domain:** `deep-learning`
**Level:** Intermediate
**Prerequisites:** basic Python, basic linear algebra, a first pass through
`perceptron-and-backpropagation` and `convolutional-neural-networks` (this
tutorial assumes you know what a CNN is and does not re-derive one)

## Summary

Object detection extends image classification from "what's in this image"
to "what's in this image, where, and how many" — a variable-length list of
labeled bounding boxes instead of one label. This tutorial builds the three
pieces of machinery every detector relies on, from scratch: **Intersection
over Union (IoU)** as the formal way to score a predicted box, **anchor
boxes** as the reason detectors predict small offsets instead of raw
coordinates, and **Non-Maximum Suppression (NMS)** as the greedy algorithm
that collapses a dense pile of overlapping raw detections into one box per
object. It also defines **mean Average Precision (mAP)** precisely. The
implementation section loads a real `torchvision.models.detection` model
pretrained on COCO, runs it on real photos, and applies the from-scratch
NMS to the model's genuinely pre-suppression raw output — showing it
collapses ~30 raw overlapping boxes down to the same result the model's
own internal NMS produces.

## Learning objectives

- Explain what a bounding box is and why object detection is a
  fundamentally harder problem than classification.
- Compute Intersection over Union (IoU) from scratch and use it to score
  real overlapping boxes.
- Explain anchor boxes: why detectors predict offsets relative to a fixed
  grid of reference boxes instead of predicting raw pixel coordinates.
- Implement Non-Maximum Suppression from scratch and use it to turn a pile
  of overlapping raw detections into a clean final set.
- Define mean Average Precision (mAP) precisely, including the
  precision-recall curve and IoU-threshold dependence.
- Run a real pretrained detector on real photos and draw its predictions.
- Name the real, still-debated engineering tradeoffs in detector design:
  confidence thresholds, IoU threshold choice, small-object detection, and
  two-stage vs. one-stage architectures.

## Contents

- `tutorial.ipynb` — theory, visuals, and implementation. Downloads a
  handful of real sample photos (from the `pytorch/vision` gallery assets)
  into `_detection_data/` on first run and runs a real pretrained
  `fasterrcnn_mobilenet_v3_large_320_fpn` detector on them.

## References

- Ren, S., He, K., Girshick, R., & Sun, J. (2015). *Faster R-CNN: Towards
  Real-Time Object Detection with Region Proposal Networks.* NeurIPS.
- Redmon, J., Divvala, S., Girshick, R., & Farhadi, A. (2016). *You Only
  Look Once: Unified, Real-Time Object Detection.* CVPR.
- Liu, W. et al. (2016). *SSD: Single Shot MultiBox Detector.* ECCV.
- Lin, T.-Y. et al. (2014). *Microsoft COCO: Common Objects in Context.*
  ECCV.
- Lin, T.-Y. et al. (2017). *Feature Pyramid Networks for Object
  Detection.* CVPR.
- Bodla, N., Singh, B., Chellappa, R., & Davis, L. S. (2017). *Soft-NMS —
  Improving Object Detection With One Line of Code.* ICCV.
- Girshick, R. (2015). *Fast R-CNN.* ICCV.
- `torchvision.models.detection` documentation,
  [pytorch.org/vision/stable/models.html#object-detection](https://pytorch.org/vision/stable/models.html#object-detection)
- Sample images: `pytorch/vision` gallery assets,
  [github.com/pytorch/vision/tree/main/gallery/assets](https://github.com/pytorch/vision/tree/main/gallery/assets)
