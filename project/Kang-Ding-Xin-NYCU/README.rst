Basic Information
=================

PolygonAreaCalaulator

`Kang-Ding-Xin-NYCU <https://github.com/Kang-Ding-Xin-NYCU>`__ for
`PolygonAreaCalaulator <https://github.com/Kang-Ding-Xin-NYCU/PolygonAreaCaculator/blob/main/README.rst>`__
:https://github.com/Kang-Ding-Xin-NYCU/PolygonAreaCaculator

Problem to Solve
================

* Easily get the the area of polygons and the image of polygons and can calculate the polygon with hole
* connect the one inner polygon vertice to one outer polygon vertice(cutline) and change the calculate direction when move from outer polygon to inner polygon(eg. counterclockwise to clockwise) 

System Architecture
===================

* input : vertices of polygons
* produces results : do some matrix operations and draw the image
* result : the area of polygons and the image of polygons

API Description
===============
code

.. code:: c++

class polygon {
public:
    void input(std::queue<float> in_x, std::queue<float> in_y);
    void print();
    float area();

private:
    std::queue<float> x, y;
};

Engineering Infrastructure
==========================

* build : make
* version control : git

Schedule
========

* Week 1 (09/20):survey the method to implement the area calculation and drawing image
* Week 2 (09/27):setting the environment to implement the functions
* Week 3 (10/04):write c++ code to implement the area calaulation
* Week 4 (10/11):write python to implement the image drawing & try to write CI and testing to make sure the major function can run properly
* Week 5 (10/18):try to find a way to accelerate the computing
* Week 6 (10/25):try to add some extra function
* Week 7 (11/01):fix any problem
* Week 8 (11/08):prepare final proposal

References
==========
* method of area counting : https://ccjou.wordpress.com/2012/05/09/%E5%88%A9%E7%94%A8%E8%A1%8C%E5%88%97%E5%BC%8F%E8%A8%88%E7%AE%97%E5%A4%9A%E9%82%8A%E5%BD%A2%E9%9D%A2%E7%A9%8D/
