Basic Information
=================

NMF with simulated annealing

Problem to Solve
================

In standard NMF (Non-negative Matrix Factorization) solving, commonly used algorithms are based on gradient descent or multiplicative update rules.
However, these methods can sometimes get stuck in local optima.
Simulated Annealing, being a global optimization method, can be used to explore a larger solution space and help find better matrix factorizations.

Prospective Users
=================

User who want to calculate NMF faster and more accurate.

System Architecture
===================

Initialization Module: Generates initial random non-negative matrices.
Simulated Annealing Engine: Handles the perturbation and acceptance of new solutions.
Objective Function: Computes the Frobenius norm to measure the quality of the solution.
Cooling Schedule: Manages temperature decay for the annealing process.

API Description
===============

Computation: C++11
Python Integration: Provide a interface for ease of use.
Example:
```python```
    from simulated_annealing_nmf import SimulatedAnnealingNMF
    
    # Initialize matrix V and parameters
    sa = SimulatedAnnealingNMF(V, m, n, k)
    
    # Set SA parameters
    sa.set_temperature(T_initial)
    sa.set_cooling_rate(alpha)
    sa.set_max_iterations(max_iter)
    
    # Run SA-NMF
    sa.run()
    
    # Retrieve matrices W and H
    W = sa.get_W()
    H = sa.get_H()
```

Engineering Infrastructure
==========================

1.Build System:
    Use CMake for the C++ code to manage builds.
    Python implementation will use a setup.py for installation and distribution.
2.Version Control:
    Use Git for version control.
3.Testing Framework:
    C++: Use Google Test for unit testing.
    Python: Use pytest for testing the Python implementation.
4.Documentation:
    Write a comprehensive README with usage instructions.

Schedule
========

* Week 1 (09/30): Research and initial project setup, including installing dependencies and setting up repositories.
* Week 2 (10/07): Implement the core simulated annealing algorithm in C++ and Python.
* Week 3 (10/14): Develop the objective function and perturbation functions.
* Week 4 (10/21): Implement the cooling schedule and complete the SA engine.
* Week 5 (10/28): Testing the system and debugging any issues.
* Week 6 (11/04): Documentation and refinement of the API for C++ and Python.
* Week 7 (11/11): Final testing, optimizations, and code refactoring.
* Week 8 (11/18): Prepare the final report, package the system, and ensure all tests pass.

References
==========

1. NMF Optimization Algorithms: Lee, Daniel D., and H. Sebastian Seung. "Algorithms for non-negative matrix factorization." Advances in neural information processing systems. 2001.
2. Simulated Annealing: Kirkpatrick, S., Gelatt, C. D., and Vecchi, M. P. "Optimization by Simulated Annealing." Science, 220(4598), 671-680. 1983.
