Voronoi Diagram
===============

Description
------------
GitHub: https://github.com/yang2829/Voronoi-Diagram

Problem to Solve
----------------
The Voronoi diagram is a decomposition of a region that any point in a sub-region is closest to the site of the sub-region.

.. image:: https://upload.wikimedia.org/wikipedia/commons/5/54/Euclidean_Voronoi_diagram.svg
   :width: 40%

Voronoi diagrams are widely used in fields such as Geographic Information Systems (GIS) and Computer Graphics.
This project is limited to 2-dimensional space. It may use Fortune's algorithm to solve it.

Prospective Users
-----------------
This system will serve as a useful tool for users needing to analyze spatial relationships and optimize region-based solutions.

System Architecture
-------------------
Input:

* A set of 2-dimensional points.
* Size of the region.

Output:

* An image filled with different colors in each sub-region.

API Description
---------------
.. code:: c++

   class Voronoi{
      int w, h;
      vector<tuple<int, int>> points;
      
      void fortune();
   };

Engineering Infrastructure
---------------------------
* Use Makefile to buid the project. Use pybind11 to buid python interface
* Use git to control version
* Documentation: README

Schedule
---------
* Week 1 - 2(09/30): Learn about setting up CI/CD on GitHub and Fortune's algorithm.
* Week 3 - 6(10/14): implement datastructure and set up CI/CD
* Week 7 - 10(11/04): implement Fortune's algorithm
* Week 11(11/25): maybe implement Divide-and-Conquer Algorithm or fix bug
* Week 12(12/02): prepare presentation


References
----------
* Fortune's algorithm https://dl.acm.org/doi/abs/10.1145/10515.10549
* Divide-and-Conquer Algorithm https://ieeexplore.ieee.org/abstract/document/9208270

