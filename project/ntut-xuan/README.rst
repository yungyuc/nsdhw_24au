PolygonDust
===========

Description
-----------

PolygonDust is an application to measure the area size of polygon.

“Dust” means we trying to shred the image into lot of pieces and measure
polygon size by these pieces.

.. image:: https://media.discordapp.net/attachments/950048467294760990/1284862080050135071/image.png?ex=66e82c8f&is=66e6db0f&hm=8f52c071f46be06d7d6d014e8551087f495e2cf1332a784079c4805429e7aea3&=&format=webp&quality=lossless&width=2880&height=848

Problem to Solve
----------------

In size measurement of ploygon, we have two methods can do it.

-  Pixel-Method: Shred the image to lot of rectangles and calculate the
   size by these rectangles.
-  Formula-Method: Calculate the polygon by formula.
   e.g. :math:`W \times H` for rectangle of :math:`r^2 \times \pi` for
   circle.

PolygonDust is used to solve size calculation by Pixel-Method. In
polygon description, we use image instead formula, that may make the
problem more easier to solve.

Expect the process steps should be:

-  `Gaussian
   Blur <https://zh.wikipedia.org/zh-tw/%E9%AB%98%E6%96%AF%E6%A8%A1%E7%B3%8A>`__
   to decrease the image noice.
-  Binarization: We trying to use `Otsu’s
   method <https://zh.wikipedia.org/wiki/%E5%A4%A7%E6%B4%A5%E7%AE%97%E6%B3%95>`__,
   it calculate the threadhold globally, and may have more efficiency to
   process binarization.
-  Shred the image to lot of piece
-  Process these piece by determine the piece is fill/not fill, and vote
   0/1.
-  By the result of voting, calculate the area of ploygon.

The gaussian blur should implement matrix calculation and Otsu’s methods
should implement K-means algorithm to solve the problem. We will
implement numerical process in C/C++ to keep its efficientcy.

Prospective Users
-----------------

Since Fomula-Method to describe the polygon may have some obstacle on
size calculation but have more accurate on measurement, this application
may help formula-method to get the size approximately by Pixel-Method
and doing cross-validation.

The user of this application can input the image by CLI (command-line
interface), and got the image size by application output.

System Architecture
-------------------

In this software, we trying to implement numerical process in C/C++. We
would like to use ``pybind11`` to convert C++ library into python
module.

We expect in C/C++, we have two classese ``GaussianBlur`` and
``OtsuMethod`` working on image process, and Python library can pass
image bytes buffer to these classes and got the byte buffer of processed
image as result.

As we got the byte buffer of processed image, we can transfer it into
images and process shredding and voting.

API Description
---------------

Since having ``GaussianBlur`` and ``OtsuMethod`` class in C++, it should
have constructor and destructor, which can passed the image byte buffer
into constructor and release the dynamic resource (if any) in
destructor. These class should have some customize parameter to
determine the particles, e.g. may passed :math:`\sigma` in
``GaussianBlur`` to determine Gaussian filter kernel and threshold
:math:`t` in ``OtsuMethod``.

Moreover, we may provide some function on ``GaussianBlur`` and
``OtsuMethod`` to validate these classes is work correctly. For example,
may having ``GetGaussianFilterKernel`` in ``GaussianBlur`` and it should
return the matrix of Gaussian filter kernel. With these function, we can
validate our ``GaussianBlur`` work correctly.

Pending Task
------------

-  [2] Properly Command-line Interface to input image and got size of
   shred pieces.

   e.g. ``./polygondust --input image.png --particles 5`` means input
   ``image.png`` and size of rectangle should be 5x5.

-  ``Pybind11`` for convert the C/C++ class into python methods.

   -  [2] Working on ``GaussianBlur`` class and make sure we can reach
      all public function in this class in Python script.
   -  [2] Working on ``OtsuMethod`` class and make sure we can reach all
      public function in this class in Python script.

-  Implement the feature on ``GaussianBlur`` and ``OtsuMethod`` class

   -  [7] Working on ``GaussianBlur`` class and trying to validate the
      ``GaussianBlur`` working properly.
   -  [7] Working on ``OtsuMethod`` class and trying to validate the
      ``OtsuMethod`` working properly.

-  [3] Implement the shred feature on Python script.

-  [3] Implement voting feature on Python script.

``[X]`` Means the weight of the task, it used to measure the task
progress.

Engineering Infrastructure
--------------------------

In this project, we have these infrastructure to make sure our project
can develop properly.

-  Version Control: Git to maintaince the version control and GitHub to
   handle the repository.
-  Build Tools (Package Tools): CMake for C/C++.
-  Testing framework: GoogleTest for C/C++ and Pytest for Python.
-  The classes and function have its unit test.
-  Coverage Supervise Tools: Codecov to supervise our testing coverage
   in these test cases.
-  Documentation: Nice ``README.md``

Schedule
--------

.. list-table:: Title
   :widths: 25 25 50
   :header-rows: 1

 * - Week
   - Task 
   - Progress (%)
 * - 1
   - System Design / Writing proposal
   - 0% (00/26)
 * - 2
   - Create GitHub Project, trying to figure how to process image on C++, and how to process command line interface on C++
   - 0% (00/26)
 * - 3
   - Implement CLI
   - 8% (02/26)
 * - 4
   - Implement CLI and doing `Pybind11` to bind "shell" classes.
   - 23% (06/26)
 * - 5
   - Implement the calculation feature of `GaussianBlur` class.
   - 23% (06/26)
 * - 6
   - Implement the calculation feature of `GaussianBlur` class.
   - 23% (06/26)
 * - 7
   - Implement the calculation feature of `GaussianBlur` class.
   - 23% (06/26)
 * - 8
   - Implement the calculation feature of `OtsuMethod` class.
   - 50% (13/26)
 * - 9
   - Implement the calculation feature of `OtsuMethod` class.
   - 50% (13/26)
 * - 10
   - Implement the calculation feature of `OtsuMethod` class.
   - 77% (20/26)
 * - 11
   - Check `GaussianBlur` and `OtsuMethod` is work property.
   - 77% (20/26)
 * - 12
   - Implement shred feature.
   - 77% (20/26)
 * - 13
   - Implement shred feature.
   - 88% (23/26)
 * - 14
   - Implement voting feature.
   - 88% (23/26)
 * - 15
   - Implement voting feature.
   - 100% (26/26)
 * - 16
   - Winding up.
   - 100% (26/26)

Reference
--------------------------
- Gaussian blur: https://en.wikipedia.org/wiki/Gaussian_blur
- Otsu's Method: https://en.wikipedia.org/wiki/Otsu%27s_method
- CodeCov: https://about.codecov.io/