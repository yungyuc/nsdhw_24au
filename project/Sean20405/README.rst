==============================================================
fftconvolve2d: FFT Convolution Operations for Image Processing
==============================================================

Basic Information
=================

GitHub: https://github.com/Sean20405/fftconvolve2d

A FFT version of
`scipy.signal.convolve2d <https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.convolve2d.html>`__.
It’s compatible to numpy array so that user can directly switch from
``convolve2d`` to it.

Problem to Solve
================

2D convolution is a fundamental operation in image processing and
computer vision, such as edge detection or blurred image. However it can
be computationally expensive when the size of images and kernels is
large. This project aims to implement and optimize 2D convolution by FFT
and other optimization methods to significantly speed up these
operations.

With a good property :math:`F(g\star h)=F(g)\times F(h)` where
:math:`F(\cdot)` means Fourier Transform and :math:`\star` represents
convolution. This means that the convolution operation in spatial domain
is equivalent to multiplication in frequency domain. Moreover, FFT (Fast
Fourier Transform) gives us a fast way to do so. Combine above two ideas,
we can get a faster approach for convolution.

Prospective Users
=================

This project aims to create a faster type of existing function
``convolve2d()``, so everyone who may use this tools would be benefit
from it. Such as

- Image processing and computer vision researchers
- Developers of image filtering and feature extraction software
- Students studing image processing

System Architecture
===================

I/O
---

-  Input (needed): An target to be convolved and a kernel. Both input
   would be list or numpy array. The dimension of both inputs should be 2
-  Output: A numpy array

Parameters (optional)
---------------------
-  mode ``str``: describe the size of output

   -  ``full`` (default): Full discrete linear convolution (The
      boundary needs padding)
   -  ``valid``: No padding
   -  ``same``: The size will be the same as input 1, centered with
      respect to the ``full`` output.

-  fillvalue: padding value
-  method: Which algorithm will be performed (default is the best one
   based on my test result)

Workflow
--------

-  Input validation
-  Padding of input image and kernel
-  Forward FFT
-  multiplication in frequency domain
-  Inverse FFT
-  Post-processing (cropping, casting to numpy array)

API Description
===============

Basically the usage will be the same as ``scipy.signal.convolve2d()``
with one more optional parmeter ``method``.

.. code:: python=

   # Example for Gaussian Blur
   import fftconvolve2d
   import cv2
   import numpy as np

   img = cv2.open('example.jpg', cv2.IMREAD_GRAYSCALE)
   GaussianKernel_1d = cv2.getGaussianKernel(45, 20)
   GaussianKernel_2d = np.outer(GaussianKernel_1d, GaussianKernel_1d.T)

   blurred_img = fftconvolve2d(img, GaussianKernel_2d) 

Engineering Infrastructure
==========================

-  Makefile (or CMake, if needed) will be used to build binaries. And 
   Python interface will be built with``pybind11``.
-  Using Git for version control and GitHub to store remote repository.
   Ideally, each commit should finish one function or fix one bug.
-  ``pytest`` is for testing correctness and performance. (compared to
   the result of the original ``convolve2d()``)
-  A README will be included for document.

Schedule
========

Planning phase (11 weeks from 09/29 to 12/08): 

- Week 1 (09/29): Learn FFT
- Week 2 (10/06): Learn FFT, decide which algorithms would be used
- Week 3 (10/13): Write test and GitHub Action for FFT and FFT convolution
- Week 4 (10/20): Implement a basic algorithm of FFT (depend on my learning)
- Week 5 (10/27): Apply into convolution & Wrap into Python and test
- Week 6 (11/03): Implement 2nd algorithm
- Week 7 (11/10): Implement 2nd algorithm & 3rd algorithm
- Week 8 (11/17): Implement 3rd algorithm
- Week 9 (11/24): Optimize by Cache Optimization or SIMD
- Week 10 (12/01): Optimize by Cache Optimization or SIMD
- Week 11 (12/08): Prepare presentation

References
==========

-  `Ch. 18: FFT Convolution \| The Scientist and Engineer’s Guide to
   Digital Signal Processing <https://www.dspguide.com/ch18/2.htm>`__
-  `Very Efficient Training of Convolutional Neural Networks using Fast
   Fourier Transform and
   Overlap-and-Add <https://arxiv.org/pdf/1601.06815>`__
-  `Efficient Processing of Deep Neural Networks: A Tutorial and
   Survey <https://arxiv.org/pdf/1703.09039>`__ Thanks to @threemonth!
-  `pytest <https://docs.pytest.org/en/stable/>`__
-  `pybind11 <https://pybind11.readthedocs.io/en/stable/index.html>`__
-  `scipy.signal.convolve2d
   <https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.convolve2d.html>`__ 