##########
 pybezier
##########

*******************
 Basic Information
*******************

**Project**: pybezier

**Github url**: https://github.com/jteng2127/pybezier

******************
 Problem to Solve
******************

In the fields of Aerodynamics, Fluid mechanics, and Modeling, it's often
essential to describe complex curves accurately. One approach involves
the use of Bezier curves, which are widely applied in computer graphics
because their smoothness and intuitive control.

The goal is to use multiple third-order (or higher order) Bezier curves
to fit the following types of curve:

#. A fourth-order Bezier curve
#. A `NACA 4-digit airfoil
   <https://zh.wikipedia.org/zh-tw/NACA%E7%BF%BC%E5%9E%8B>`_
#. Any discretely sampled curve (e.g. `Contour line
   <https://en.wikipedia.org/wiki/Contour_line>`_)
#. Any curve that can be expressed by a formula (e.g. `Superformula
   <https://en.wikipedia.org/wiki/Superformula>`_ curve)

The potential solutions are listed in :ref:`potential-solutions`

*********************
 System Architecture
*********************

The algorithm will be implemented in C++ for performance and efficiency,
with Python bindings provided via pybind11.

Input
=====

The fitting target can be one of the following:

-  A list of points representing the curve

   -  Around 20 to 200 points, depends on the complexity of the curve

-  A function that samples point along the curve

Fitting parameters:

-  The desired order of the Bezier curve
-  The maximum allowable error for fitting
-  Maximum number of iterations allowed for the fitting algorithm to
   converge

Results
=======

-  A set of Bezier curve object that approximate the input curve

-  The fitting history, contains the Bezier curve objects and error
   values for each iterations

   -  To prevent overfitting, the error calculation tends to use 3x to
      5x more points than the training data

*****************
 API Description
*****************

.. code:: python

   class Point:
      def __init__(self, x: float, y: float):
         pass

   class History:
      def __init__(self, bezier_curves: List[BezierCurve], error: float):
         pass

   class BezierCurve:
      def __init__(self, control_points: List[Point]):
         pass

      def sample(self, position: float) -> Point:
         """
         0 <= position <= 1
         return a Point
         """

   def fit_Bezier_curve(points, order: int = 3, target_error: float = 1e-3, max_iter: int = 100, closed: bool = False) -> Tuple[List[BezierCurve], float]:
      """
      return BezierCurve, error
      """

   def sample_points(curve_func: Callable[[float], Point], num_points: int = 100) -> List[Point]:
      """
      call curve_func(t) with 0 <= t <= 1 to get xy point
      """

   def calculate_error(bezier_curve, target_points) -> float:
      """
      the target_points should be evenly sampled in t
      """

****************************
 Engineering Infrastructure
****************************

Use Makefile to define how to build the project.

Use Github actions for automatic building.

*********************
 Git branching model
*********************

Only `main` branch because:

#. This is a term project
#. There's only one developer :D

*******************
 Commit convention
*******************

A commit message should as below:

.. code::

   <type>[indicator]: <description>

   [body]

   [footer]

Commit types:

-  `feat`: Add a new feature
-  `fix`: Fix a bug
-  `docs`: Update documentation
-  `refactor`: Refactor code
-  `test`: Add or update tests
-  `chore`: Update settings, dependencies, or other non-functional tasks
-  `build`: Update build tools or scripts
-  `ci`: Update CI configuration
-  `perf`: Improve performance
-  `style`: Fix code formatting

Indicators:

-  `!`: Breaking change
-  `*`: The commit has a body or footer

**********
 Schedule
**********

#. 9/16~ (w3~w4)

   -  Setup basic project structure and dependencies
   -  Write some experimenting code about pybind11
   -  Setup unit test with experimenting code
   -  Explore other relative problems to solve

#. 9/30~ (w5~w6)

   -  Implement evaluating algorithm (error calculation)
   -  Survey and implement basic fitting algorithm
   -  Setup building flow
   -  Write unit test

#. 10/14~ (w7~)

   -  Visualize the fitting result
   -  Implement and optimize fitting algorithm

#. 12/09~ (w15)

   -  Prepare final report

.. _references:

************
 References
************

.. _potential-solutions:

Potential solutions
===================

-  `利用三階貝茲曲線逼近四階貝茲曲線__臺灣博碩士論文知識加值系統
   <https://hdl.handle.net/11296/a779x5>`_
-  `Least squares <https://en.wikipedia.org/wiki/Least_squares>`_

Problems
========

-  `Use Bezier curve to fit NACA 4-digit airfoil · Issue #320 ·
   solvcon/modmesh <https://github.com/solvcon/modmesh/issues/320>`_
