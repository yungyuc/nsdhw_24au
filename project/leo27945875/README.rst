========
Proposal
========

Basic Information
=================

* Project: pyGMRES 
* GitHub: https://github.com/leo27945875/pyGMRES

Problem to Solve
================

The **Generalized-Minimal-Residual** (GMRES) solves a *large scale linear 
system Ax = b* using efficient iterative method. This project will be 
implemented in both dense and sparse matrix versions.

Prospective Users
=================

GMRES can be used in many kinds of applications, as long as the application 
needs to solve large scale linear systems. For instance: construction 
engineering (structural analysis), EDA tools (IC design verification), ...etc.

System Architecture
===================

This project will provide Python API and C++ implementation with pybind11 to 
connect Python and C++. If time allows, there will be a multi-threading version 
for matrix multiplication with OpenMP.

Input: 
   A matrix A and a vector b in dense matrices (numpy array) or sparse matrices 
   (scipy CSR sparse matrix)
  
Output: 
  A vector x in dense matrix (numpy array) or sparse matrix (scipy CSR sparse 
  matrix)

API Description
===============

**For dense matrices:**

.. code-block:: python
    
    # Solve a large-scale linear system Ax = b.
    
    import pyGMRES
    import numpy as np
    
    mat_A: np.ndarray = ...
    vec_b: np.ndarray = ...
    vec_x: np.ndarray = pyGMRES.solve_dense(mat_A, vec_b)
    
    
**For sparse matrices:**

.. code-block:: python
    
    # Solve a large-scale linear system Ax = b.
    
    import pyGMRES
    import scipy.sparse as sp
    
    mat_A: sp.csr_matrix = ...
    vec_b: sp.csr_matrix = ...
    vec_x: sp.csr_matrix = pyGMRES.solve_sparse(mat_A, vec_b)
	

Engineering Infrastructure
==========================

Automatic build system and how to build your program:
    Because only Python API will be provided in this project, I'll use the 
    buliding tools in pybind11 to build the system. But perhaps the Makefile 
    will also be used for debugging. 

Version control:
    There will be two branches for version control. One is the **master** 
    branch, another is the **dev** branch. Once a new function in **dev** is 
    finished and passes the unitest, then merge the **dev** into **master**.
    
Testing framework:
    C++: GoogleTest, Python: pytest


Documentation:
    The Markdown will be used for writing documentation as well as the README 
    in GitHub repo.

Schedule
========

* Week 1~2 (09/23~10/07): Study the GMRES algorithm and get familiar with the 
  unitest, Github Action and pybind11.
* Week 3~5 (10/07~10/28): Setting up the enviroment and implement the GMRES in 
  dense matrix.
* Week 6~8 (10/28~11/11): Implementing the sparse matrix version of GMRES.
* Week 9~10 (11/11~11/18): Write down the documentation.
* Week 10~ (11/18~): Prepare final report.


References
==========

| `Motivation of this project`_
| `GMRES algorithm`_


.. _`Motivation of this project`: https://www.104.com.tw/job/8dg3i?jobsource=google
.. _`GMRES algorithm`: https://zh.wikipedia.org/zh-tw/%E5%B9%BF%E4%B9%89%E6%9C%80%E5%B0%8F%E6%AE%8B%E9%87%8F%E6%96%B9%E6%B3%95