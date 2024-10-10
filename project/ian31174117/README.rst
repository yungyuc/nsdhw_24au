#######################
 SimpleEigenCalculator
#######################

*******************
 Basic Information
*******************

The project will be developed `here
<https://github.com/ian31174117/SimpleEigenCalculator>`_

The calculation of Eigen values and vectors is common in scientific
research and model inference/training, for example, PCA. This project,
Simple Eigen Calculator, aims to provide a light-weighted API in C/C++
to calculate Eigen values and vectors. A Python module wrapped with
pybind11 will also be provided.

******************
 Problem to Solve
******************

There have been several libraries to calculate Eigen values and vectors,
such as `Eigen <https://eigen.tuxfamily.org/index.php?title=Main_Page>`_
and `Armadillo <https://arma.sourceforge.net/>`_. However, for a
low-level platform like a MCU, which may not even run an OS, loading
such a library is impractical.

This project may benefit those who are working on a low-level platform
with need of Eigen calculation and those who are interested in the
implementation of Eigen calculation algorithms.

The following functions will be implemented with least dependencies
included:

#. QR algorithm to calculate Eigen values and vectors
#. Jacobi algorithm to calculate Eigen values and vectors
#. Parallel computation of Eigen values and vectors if supported by the
   platform
#. Optimization for speed, memory/flash usage, and accuracy

*********************
 System Architecture
*********************

The system of Simple Eigen Calculator will consist of the following
components:

#. QR decomposition module: This module decomposes a matrix A to A = QR.
#. Jacobi matrix module: This module generates a rotation matrix to
   diagonalize a matrix using Jacobian algorithm.
#. Eigen calculation module: This module calculates Eigen values and
   vectors using QR or Jacobi algorithm, depending on the need of user.
#. Parallel computation module: This module will be implemented if the
   platform supports parallel computation.
#. Basic linear algebra module: Since we're using the least libraries
   posible, some basic linear algebra opeartions have to be implemented.

The workflow of the system will be as follows:

#. User gives a matrix A, the algorithm to adopt, the tolerance of
   Jacobian algorithm if adopted, and the ability to use parallel
   computation on the platform.

#. The system performs iteration using the given algorithm and returns
   Eigen values and vectors.

#. The eigenvectors will be sorted according to the eigenvalues.

*****************
 API Description
*****************

C/C++ API:

.. code:: cpp

   #include<"SimpleEigenCalculator.h">
   int main(){
       float matrix[10][10] = sample_matrix; // a 2D array representing a matrix
       // Support on other data structures will be added if possible
       //Maybe design a data structure to efficiently hold data for this project
       SECMatrix<float> matrix(sample_matrix); // a data structure to hold the matrix
       const char* algo = "Jacobian"; // or "QR", the algorithm to adopt
       float tol = 1e-6; // the tolerance of Jacobian algorithm
       SimpleEigenCalculator sec(algo, tol, sort_eigen_vec = true); // create an instance of SimpleEigenCalculator
       // Maximum iterations can also be set if needed
       sec.calculate(SECMatrix); // calculate the Eigen values and vectors
       auto eigen_values = sec.get_eigen_values(); // get the Eigen values
       auto eigen_vectors = sec.get_eigen_vectors(); // get the Eigen vectors
   }

Python API:

.. code:: python

   import SimpleEigenCalculator
   matrix = sample_matrix # a 2D list representing a matrix
   algo = "Jacobian" # or "QR", the algorithm to adopt
   tol = 1e-6 # the tolerance of Jacobian algorithm
   sec = SimpleEigenCalculator(algo, tol, sort_eigen_vec = True) # create an instance of SimpleEigenCalculator
   sec.calculate(matrix) # calculate the Eigen values and vectors
   eigen_values = sec.get_eigen_values() # get the Eigen values
   eigen_vectors = sec.get_eigen_vectors() # get the Eigen vectors

.. note::

   The Python module will be wrapped with pybind11. The API may be
   adjusted according to the implementation.

****************************
 Engineering Infrastructure
****************************

The infrastructure is briefly listed below:

#. Version control: The project will be hosted fully on GitHub.
#. Building the program: Since it is a light-weighted project, a simple
   Makefile will suffice.
#. Testing: Unit tests will be written using Google Test for C/C++ and
   pytest for Python.
#. Documentation: The documentation will be in both common README files
   and docstrings in the code.

**********
 Schedule
**********

-  Week 1: Building the basic structure of the project, make basic
   testing modules/design of CI
-  Week 2: Implementing the basic linear algebra module, revise the
   structure of testing
-  Week 3: Implementing the QR decomposition module
-  Week 4: Implementing the QR decomposition module
-  Week 5: Implementing the Jacobian algorithm module
-  Week 6: Implementing the parallel computation module and optimization
-  Week 7: Binding the Python module
-  Week 8: Final testing and presentation

************
 References
************

#. `Eigen <https://eigen.tuxfamily.org/index.php?title=Main_Page>`_
#. `Armadillo <https://arma.sourceforge.net/>`_
