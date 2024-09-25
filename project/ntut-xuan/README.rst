PolygonDust - An application to calcualate the complex polygon area.
===============================================================================


Description
-------------------------------------------------------------------------------

PolygonDust is an application to calculate the polygon area. 

We trying to calculate the polygon with cell of grid and measure the size of 
polygon.

We support that you describe complex polygon and get the area of complex polygon. 

For complex polygon, we support that you can input two or more polygon 
to doing bitwise operator like union, difference or clip. 

You can select what polygon you want to doing with the pervious polygon.

.. image:: https://media.discordapp.net/attachments/950048467294760990/1284862080050135071/image.png?ex=66e82c8f&is=66e6db0f&hm=8f52c071f46be06d7d6d014e8551087f495e2cf1332a784079c4805429e7aea3&=&format=webp&quality=lossless&width=2880&height=848


How do we describe the polygon
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We will trying to describe the polygon with the ordered point set, it will
store the vertex of the polygon clockwised or counterclockwised.

In ordered point set, it will contains lot of x and y pair 
to describe the vertex of polygon.

The ordered point set file may be Wavefront `.obj` file.

For example: A square may have these point: (0, 0), (3, 0), (3, 3) and (0, 3).


The way we calculate the size of polygon
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
We are trying to shard the polygon with the gird. 
The grid contains lot of cell. 

If the cell is in the polygon, we will mark it and calculate the mark the cell 
to get the approximately size.



Problem to solve
-------------------------------------------------------------------------------
This application support that calculate the size of complex polygon. 
It can be a normal polygon to get the approx area, and it can composite 
lot of polygon to make a complex polygon and get the approx area.


The procedure that we solve the problem:

- Input the point sets for polygons
- Adjust the specific polygon is union/difference/clip the base polygon.
- Trying to mark the cell in grid.
- Calculate how much cell is marked and calculate the approximately area.


Prospective Users
-------------------------------------------------------------------------------
This application can help the user that trying to get the size of 
complex polygon. 

Since it may complex to calculate the polygon composite lot of polygon, 
it should be a nice tool to complete it.

The user may trying to input points set file with CLI and adjust the bitwise 
operator to describe the complex polygon. 

The idea is based on how complex polygon described in SVG files.


System Architecture
-------------------------------------------------------------------------------
In this software, we trying to implement numerical process in C/C++. 
e would like to use pybind11 to convert C++ library into python module.

We expect two classes `Polygon` and `Point` to describe the polygon and point. 

Also, we may have a function to determine the cell is in the polygon or not by 
describing the top-left coordinate of cell and the width/height of cell.


API Description
-------------------------------------------------------------------------------
`Polygon` class will have a constructor and destructor 
to input multiple `Point`. 
The `Point` class will have a constructor to input the coordinate x and y. 

**For more description we may need to design of it. 
It will added in the future.**


Engineering Infrastructure
-------------------------------------------------------------------------------
In this project, we have these infrastructure to make sure our project
can develop properly.

-  Version Control: Git to maintaince the version control and GitHub to
   handle the repository.
-  Build Tools (Package Tools): CMake for C/C++.
-  Testing framework: GoogleTest for C/C++ and Pytest for Python. 
   We will test all the utiltiy function or classes 
   to make sure it keeps high test coverage.


Schedule
-------------------------------------------------------------------------------

.. list-table::

 * - Week
   - Task 
   - Progress (%)
 * - 1
   - System Design / Writing proposal
   - (??/26)
The `Point` class will have a constructor to input the 
   - Implement CLI and doing `Pybind11` to bind "shell" classes.
   - (??/26)
 * - 5
   - Implement "Input Polygon" feature
   - (??/26)
 * - 6
   - Implement "Input Polygon" feature
   - (??/26)
 * - 7
   - Implement "Input Polygon" feature
   - (??/26)
 * - 8
   - Implement "Polygon Calculation" feature
   - (??/26)
 * - 9
   - Implement "Polygon Calculation" feature
   - (??/26)
 * - 10
   - Implement "Polygon Calculation" feature
   - (??/26)
 * - 11
   - Implement "Polygon Bitwise Operation" feature
   - (??/26)
 * - 12
   - Implement "Polygon Bitwise Operation" feature
   - (??/26)
 * - 13
   - Implement "Polygon Bitwise Operation" feature
   - (??/26)
 * - 14
   - Implement "Polygon Bitwise Operation" feature
   - (??/26)
 * - 15
   - Implement "Polygon Bitwise Operation" feature
   - (??/26)
 * - 16
   - Winding up
   - (??/26)

Reference
-------------------------------------------------------------------------------
- CodeCov: https://about.codecov.io/
- Wavefront .obj file: https://en.wikipedia.org/wiki/Wavefront_.obj_file

