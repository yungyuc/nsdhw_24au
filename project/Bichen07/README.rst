
#################
VoronoiHybrid
#################

*****************
Basic Information
*****************
* **Project Name**: VoronoiHybrid
* **Github Repo**: https://github.com/Bichen07/VoronoiHybrid
The Voronoi Diagram is a well know data structure in computetational geometry.
used for partitioning a plane into regions based on distance to a set of points. 
Each point (called a seed or site) has a corresponding region consisting of all the points closer to that seed than to any other.

Voronoi Diagrams have applications in various fields,
such as spatial analysis, nearest-neighbor searches, and computational physics.

*****************
Problem to Solve
*****************
Voronoi Diagrams are used in diverse fields ranging from geography and robotics to machine learning. 
Calculating Voronoi diagrams efficiently is crucial in large-scale simulations and real-time applications.

However, creating Voronoi diagrams in Python using libraries like SciPy can become inefficient when applied to large datasets 
or when extended to 3D or higher dimensions. C++ is more suited for these heavy computational tasks but lacks a flexible user interface like Python.

The main problem VoronoiHybrid addresses is combining C++'s computational speed for constructing Voronoi diagrams with Python's ease of use 
and data visualization libraries. We aim to achieve this without data duplication between the two languages, ensuring fast, efficient, and memory-optimal operations.

*****************
Prospective Users
*****************
The users of VoronoiHybrid will primarily be researchers, engineers, and developers in the following fields:

* **Geospatial Analysis**: For dividing geographical regions, territory mapping, and urban planning.
* **Robotics**: For tasks such as path planning and sensor network design.
* **Physics Simulations**: Modeling atomic structures or simulating particle interactions.
* **Machine Learning**: For clustering, nearest-neighbor searches, and boundary definitions.

*****************
System Architecture
*****************
The VoronoiHybrid system will be composed of two main parts:

* **Core Voronoi Computation (C++11)**: 
Efficient computation of the Voronoi diagram will be done in C++ 
using a combination of computational geometry algorithms (Fortune’s sweep line algorithm or Delaunay triangulation). 
The C++ implementation will manage memory efficiently and handle large datasets.

* **Python Integration (pybind11)**: 
I will provide a Python interface for ease of use and integration with Python-based libraries 
such as Matplotlib for visualization and NumPy for data manipulation. 
This interface will allow users to compute Voronoi diagrams from Python without significant performance penalties or memory duplication.


*****************
API Description
*****************

Function in Python
++++++++++++++++++
* ``compute()``: Constructs the Voronoi diagram and returns vertices and edges. 

* ``get_cells()``: Returns the Voronoi cells, each corresponding to a seed point. 

* ``get_edges()``: Returns edges of the diagram, useful for visualization. 

* ``get_vertices()``: Returns the vertices at the intersection of the edges.


*****************
Engineering Infrastructure
*****************
The project will use:

* Unit Testing: C++ unit tests will be created using Google Test for validating the core computation of the Voronoi diagrams. 
Python tests will use pytest to ensure the Python interface behaves correctly and efficiently.

* Continuous Integration (CI): GitHub Actions will be used to automatically run tests on each commit, 
ensuring the correctness of the C++ and Python integration, as well as performance regressions.

* Code Documentation: Documentation will be provided in both Doxygen (for C++) and Sphinx (for Python), 
ensuring that developers can easily extend and use the system.

*****************
Schedule
*****************
1. Week 1 (10/07): 
    * Research existing methods (Python libraries like SciPy) and C++ implementations. 
    * Study Voronoi algorithms (e.g., Fortune's Algorithm) and Python/C++ integration with Pybind11.

2. Week 2 (10/14): 
    * Design the hybrid architecture, deciding which parts to implement in C++ and Python. 
    * Set up project structure and basic Python-C++ integration using Pybind11.

3. Week 3 (10/21): 
    * Implement core Voronoi diagram algorithm in C++. Test correctness using simple cases.

4. Week 4 (10/28): 
    * Bind the C++ code to Python using Pybind11. Ensure the Python interface can generate Voronoi diagrams using the C++ core.

5. Week 5 (11/04): 
    * Optimize memory sharing between Python and C++ for large datasets.

6. Week 6 (11/11): 
    * Extend the C++ implementation to support 3D Voronoi diagrams.

7. Week 7 (11/18): 
    * Compare the hybrid system’s performance with existing methods (SciPy) for large datasets. Optimize further based on benchmarks.

8. Week 8 (11/25): 
    * Complete testing for 2D and 3D cases. Write user documentation and prepare for the project presentation.

9. Week 9 (12/02): 
    * Refactor code for clarity.

10. Week 10 (12/09): 
    * Finalize the presentation, highlighting performance gains and real-world applications.

11. Week 11 (12/16): 
    * Project presentation

*****************
References
*****************
* https://yyc.solvcon.net/en/latest/nsd/project/project_simple_array.html