======
PicoLA
======

PicoLA: a compact C++ library for doing linear algebra computations

Basic Information
=================

`PicoLA` aims to provide coding experience similiar to MATLAB and is capable to run on resource-limited devices without installing extra dependent packages.

See more information in its repository: https://github.com/OscarShiang/PicoLA

Problem to Solve
================

Linear algebra is frequently used by real-world applications. It does not only appear in large scale high performance servers, it usually needs to be shipped with embedded devices as products as well.

However, porting linear algebra stuffes from idea to product sometimes become a pain for the developers. Since the syntax and the properties of MATLAB script may differs from the languages used by embedded developers. Even if it works, it could be not easy to solve the dependencies of the library and impossible to utilize on bare-metal platforms.

The library tries to deal with the problem by supporting similiar syntax using by MATLAB developers and not to compromise the performance in the same time.

The following operations are considered to be implemented:

1. Vector and matrix generation
2. Related operations (e.g. add, substract, multiply, cross, normalize, sum, average, ...)
3. Signal processing (e.g. fast Fourier transform and its inverse) 

Prospective Users
=================

`PicoLA` will help developers, who aims to port some linear algebra works from MATLAB scripts, to transfer the code with slightly extra effort.

System Architecture
===================

`PicoLA` will be developed with C++ since it is expected to be run on some devices that is not running with an OS. Thus dynamic memory space allocation is not allowed in this library. It will used the buffer allocated when the instance is initiated to do all the calculations hoping to eliminate the time spending on resizing and filling values into the memory space.

In the mean while, picoLA will utilize the template feature supported by C++ to extend the base class and reducing the repeating jobs of creating similiar classes.

API Description
===============

All the classes including vector and matrix are under the namespace of `picola` to prevent naming confliction. Each of the class will provide several constructors for initializing without data of with some pre-defined data. For the member functions, they provide interface to get data in different ways, like retrieving matrix diagnonals.

To make the developers easy to use, most of the operations will be implemented via operator overloading to not be confused when using the library.

Engineering Infrastructure
==========================

The system is composed by the following parts

- Version Control: Git
- Testing Framwork: GoogleTest
- Documentation: hdoc hosted by Github Pages
- Automatic build and test system: GitHub Action

Since the whole project is composed by C++, we choose GoogleTest as the unit-testing framework. Leverage GitHub Actions to do testing whenever the code is pushed onto branches. As GitHub Action supports Apple M1 Machines, we can ensure that all the hardware-related instructions can be properly compiled and run on actual machines.

For public APIs, we try use [hdoc](https://hdoc.io/) to generate human-readable document. This framework can also be builded and released via GitHub Action. So that we can simply host the document page on GitHub.

Schedule
========

- Week 1: Setup the infrastructures
- Week 2: Define the library's data structures
- Week 3: Implement fundamental operations for vector and matrix
- Week 4: Research for implement vector and matrix operations with SIMD instructions
- Week 5: Add SIMD support into the library
- Week 6: Create unit tests and set onto GitHub Actions
- Week 7: Debug the code and fix errors found in unit tests
- Week 8: Write and publish the API document on GitHub Pages

References
==========

- Armadillo (C++ library for linear algebra & scientific computing): https://arma.sourceforge.net/
