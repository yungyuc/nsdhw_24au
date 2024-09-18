################################
 Boolean Operations on Polygons
################################

*******************
 Basic Information
*******************
**Project**: Boolean Operations on Polygons

**GitHub**: https://github.com/hfkfo/Boolean_Operations_on_Polygons

******************
 Problem to Solve
******************
**Boolean operations on polygons** involve combining two or more polygons using set operations like union, intersection, difference, and exclusive-or (XOR).

.. image:: https://miro.medium.com/v2/resize:fit:1400/format:webp/1*-HFaUxQdqiibk27ovbT8QA.png

Boolean operations on polygons are critical in various fields such as computer graphics, computational geometry, GIS (Geographic Information Systems), 
CAD (Computer-Aided Design), and game development.

The main objective of this project is to compute Boolean operations on polygons.

*********************
 System Architecture
*********************

**Input** : 
    - Coordinates of the vertices of a polygons
    - The boolean operation

**Process** : 
    - Cut the edges of polygon into smaller segments at the intersection points. This way, all edges to be processed will only intersect at endpoints.
    - Based on the boolean operation, select the edges depending on whether they lie inside the other polygon's interior.
    - Join the edges together to obtain the output.

**Output** : 
    - Get coordinates of the vertices of a polygons
    - Use python to draw the result.

*****************
 API Description
*****************

.. code:: c++

    class Bool_Op{
        int op;
        // Union = 0 , Intersection = 1, Difference = 2, XOR = 3
        vector<Polygon> p_list;
        // The input of Polygons
        void cutting_edge();
        void selecting_edge();
        void joining_edge();
    };



****************************
 Engineering Infrastructure
****************************

- Build : Make
- Version control : git

**********
 Schedule
**********

* Week 1-2 (09/30): Setup the infrastructures and learn how to do CI in github.
* Week 3-4 (10/14): Write C++ code to calculate Boolean Operations on Polygons. 
* Week 5 (10/28): Write python code to visualize the result.
* Week 6 (11/04): Binding with Python.
* Week 7 (11/11): Flextime to do any adjustments to this project.
* Week 8 (11/18): Prepare Final Report.

************
 References
************

- A new algorithm for computing Boolean operations on polygons : https://www.sciencedirect.com/science/article/pii/S0098300408002793
