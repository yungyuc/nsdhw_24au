=================
Project
=================
Efficient-Eigenvalue-Approximation-using-Gersgorin-Theorem-and-PCA-for-Dimensionality-Reduction 

Basic Information
=================

GitHub repository :https://github.com/LienShark/Efficient-Eigenvalue-Approximation-using-Gersgorin-Theorem-and-PCA-for-Dimensionality-Reduction
About:I will try to use Gersgorin Theorem to find eigenvalue approximation to do spectral,
hope can speed up PCA compression as much as possible while sacrificing the least accuracy,
then provide APIs for related applications that will be used!

Problem to Solve
================
This project aims to solve the problem of calculating eigenvalues ​​and dimensionality reduction of 
large matrices. This problem is very common in machine learning, numerical linear algebra 
and scientific computing. Especially in natural language processing (NLP), genetic data analysis 
and big data processing, as the size of data grows, the limitations of existing tools 
in terms of speed and memory consumption become increasingly obvious.

We will apply Gersgorin Theorem to estimate the eigenvalues ​​of large matrices, 
and then perform dimensionality reduction through principal component analysis (PCA)

Introduce of Gersgorin Theorem:s a theory used to approximate the eigenvalues ​​of matrices. 
This theorem states that given a complex matrix A ,All eigenvalues ​​of a matrix lie within some specific disks on the plane, 
these disks are called Gersgorin disks.

Prospective Users
=================
I expect that the calculation time can be shortened and efficiency improved in data-intensive research 
(such as genetic data analysis, text analysis of large corpora). Since I have reduced the accuracy a little 
in exchange for faster calculation speed, I expect I hope that my project can serve as a pilot test for 
these data-intensive research ideas; I also hope that it can enable personal computers to do tasks such as 
training large-scale NLP.

In addition, I will also apply it to financial modeling, machine learning and big data processing, 
and use my project to reduce memory and computing costs in the data processing process. 
I hope it can have more practical application value.


System Architecture
===================

1.input and output
  input:massive matrix
  output:The approximate eigenvalues ​​estimated by Gersgorin Theorem, and the low-dimensional matrix reduced by PCA.
2.System process
  2.1 Read the input matrix and preprocess it.
  2.2 Use Gersgorin Theorem to calculate the approximate range of eigenvalues.
  2.3 Base on Gersgorin Theorem to guess approximate eigenvalues,the solution TBD.
  2.4 Apply PCA for dimensionality reduction.
  2.5 Output the results to the Python API for subsequent analysis by users.
3.Module division
  Eigenvalue estimation module
  Dimensionality reduction module
  API module

API Description
===============
C++ API: Provides the GersgorinEigenAppro class to implement eigenvalue approximation,
and works with the PCAReduc class to implement dimensionality reduction.

Python API: Use pybind11 to wrap C++ functions and provide high-level interfaces for users to use directly,
such as approximate_eigenvalue(matrix) and perform_pca(matrix, n_components).

Application API:If time permits, I hope to make it
  gerNLP: version for NLP use
  gerML: gives the version used by ML
  gerGene: the version given to the gene bank to use
  gerFinance: the version used by the financial model

Engineering Infrastructure
==========================
Automated build system: Use CMake to set up a C++ build system, and use setuptools to build Python packages.
Version control: Use Git for version management, and all development processes will be submitted to the GitHub project repository.

========
* Planning phase (6 weeks from 09/16 to 10/20):survey the background knowledage, as bellow:
  1.Matrix Theory Especially on Gersgorin-Theorem
  2.How to narrow down the possible range of eigenvalues
  3.knowledage about NLP and ML
  4.knowledage about Finance and genetic information
* Week 1 (10/21): Write preliminary architecture and simple algorithm implementation
* Week 2 (10/28): Complete the implementation and test cases of Gersgorin Theorem,
                  and use the small matrix to test the difference between the obtained eigenvalues ​​and the actual value,
                  and think about ways to improve it.
* Week 3 (11/04): Complete the PCA module implementation and conduct basic testing.
* Week 4 (11/11): Optimize memory management and try to process large-scale matrices to see 
                  if it can run successfully under extremely large matrices.
* Week 5 (11/18): Integrate API and complete documentation.
* Week 6 (11/25): Try and develop mods for different applications like Finance and NLP
* Week 7 (12/02): Correct potential problems and optimize algorithm performance.
* Week 8 (12/09): Write reports and prepare final presentations.

References
==========
1.Matrix Theory - basic results and techiques 2nd edition by Fuzhen Zhang

