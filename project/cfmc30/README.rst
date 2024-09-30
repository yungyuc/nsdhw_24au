FDCT: Fast Discrete Cosine Transformation Library
=================================================

`GitHub Repository <https://github.com/cfmc30/FDCT>`_

Basic Information
=================

FDCT is a Python library built using C++, designed to compute Discrete Cosine
Transformations (DCT) and invert discrete cosine transformation efficiently.
By leveraging O(nlog(n)) complexity, FDCT improves performance through optimized
parallelism and support for CPU SIMD(Single Instruction, Multiple Data) instructions.
The library is suitable for large-scale data transformation tasks, especially in digital
signal and image processing.

Problem to Solve
================

In the field of digital signal processing, transformations such as the Discrete Fourier
Transformation (DFT) and Discrete Cosine Transformation (DCT) are indispensable.
These transformations decompose signals or images into their frequency components.
While Fast Fourier Transformation (FFT) has optimized the DFT to an O(nlog(n)) complexity,
an analogous efficient method for DCT is still a necessity for modern applications.

The DCT is widely used in image compression(JPEG), audio compression(MP3), and other signal
processing tasks. However, as data sizes grow, performing DCT on high-resolution images or
large datasets becomes vomputationaly expensive.

FDCT  provides a fast 1D and 2D DCT algorithm that brings down the time complexity to O(nlog(n)) using
parallelism and SIMD to take advantage of modern multicore processors.


Prospective Users
=================

FDCP will be valuable in fieds where DCT is used extensively:

* Image processing and compression
* Audio processing and compression

System Architecture
===================

FDCT is built as a Python extension using C++, and interacts with Python codebases
through Numpy arrays as the primary data structure. The key architectural elements
are:

#. Input/Output

   * FDCT accepts 1D or 2D NumPy array as input, where each element represents a
     pixel intensity (for images) or a signal value.

   * The library outputs the DCT result as another NumPy array of the same dimensions.

#. Configuration Options:

   * Multithreading: Users can enable or disable multithreading,
     depending on their hardware capabilities.

   * SIMD Optimization: The library allows specifying whether SIMD support is enabled,
     taking advantage of CPU architectures that provide these instructions (e.g. AVX or SSE).


API Description
===============

Python API
----------

FDCT will provide a Python interface that integrates with the NumPy library,
making it easy for Python developers to perform discrete cosine transformations.
Here is a simple example::
  import numpy as np
  import fdct

  # Create a 2D NumPy array (e.g., an image)
  data = np.random.rand(256, 256)

  # Perform 2D Discrete Cosine Transformation
  dct_result = fdct.dct2(data, multithread=True, simd=True)

  # Perform Inverse DCT
  idct_result = fdct.idct2(dct_result)

  # Display the result
  print(idct_result)


Engineering Infrastructure
==========================

1. Automatic build system
   This project use CMake to accomplish automatic build system, and also use GitHub
   CI to automatic build and test the library at each commit.
2. Version control
   Git is the main version control tool for this project.
   After complete main archtecture of the project. Each functionality will be implemented
   in a branch. After complete of implementation, it will be merged to the dev branch.
   The stable branch will merge when the code in dev branch is fully tested.
3. Testing framework
   Each deploy will test the library with comparing with the result of ``scipy.fftpack.dct``.
4. Documentation
   Each api will be will documented during development.


Schedule
========

* Planning phase (09/16-10/07) Learning DCT fundamental, Pybind ,and CI
* Week 1 (10/14): Basic project structure construction and bind with Python
* Week 2 (10/21): Deploy CI and automatic testing
* Week 3 (10/28): Basic algorithm implementation
* Week 4 (11/04): Optimization with SIMD and multithreading (1/2)
* Week 5 (11/11): Optimization with SIMD and multithreading (2/3)
* Week 6 (11/18): Optimization with SIMD and multithreading (3/3)
* Week 7 (11/25): Benchmark and validation
* Week 8 (12/02): Making Presentation slides and documentation

References
==========
1. Discrete cosine transformation:
   https://en.wikipedia.org/wiki/Discrete_cosine_transform
2. The Discrete Cosine Transform(DCT): Theory and Application
   https://coehuman.uodiyala.edu.iq/uploads/Coehuman%20library%20pdf/%D9%83%D8%AA%D8%A8%20%D8%A7%D9%84%D8%B1%D9%8A%D8%A7%D8%B6%D9%8A%D8%A7%D8%AA%20Mathematics%20books/Wavelets/25%20(2).pdf
3. C. W. Kok, Fast algorithm for computing discrete cosine transform
   https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=558495
