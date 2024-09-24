#################
VisualizeWifi
#################


*****************
Basic Information
*****************
* **Project Name**: VisualizeWifi
* **Github Repo**: https://github.com/hsiehbingting/VisualizeWifi

  
*****************
Problem to Solve
*****************
The project aims to assist in the design and construction of wireless
network environments by using T-IPLM (Tata Indoor Path Loss Model)
to predict and visualize indoor signal strength distribution.
  
Because T-IPLM takes into account the material and quantity of obstacles,
T-IPLM has better accuracy than some popular path loss models such as 
ITU-R and logarithmic distance.

  
*****************
Prospective Users
*****************
Anyone who wants to set up or analyze an indoor 
wireless network environment.


*******************
System Architecture
*******************
* **Input**: 
    The user inputs room size, wall position and materials, and signal
    source parameters in the Python interface.

* **Compute**:
    The C++ module uses the T-IPLM model to calculate the path loss at
    various points in the room, based on the signal source location and
    the room's structural properties (wall positions and materials).

* **Analyze results**:
    The C++ module computes the signal strength at each point by combining
    the signal source strength with the previously calculated path loss.

* **Visualize results**:
    Use Matplotlib to visualize the signal distribution, generating 2D 
    heatmap of the WiFi signal coverage.


*****************
API Description
*****************

Function in Python
++++++++++++++++++
* ``add_room``: Define the room's size as a 2D plane.

* ``add_obstacle``: Add an obstacle to the room using the specified material.
    
    .. note::
        Walls are treated as lines with no thickness, while pillars are
        represented as 60x60cm squares.

* ``set_signal_source``: Set the signal source's position and power.

* ``visualize_signal_distribution``: Visualize the signal strength.


Function in C++
+++++++++++++++++
* ``compute_path_loss``: Compute the path loss at a given point.

* ``compute_signal_strength``: calculates the signal strength at a given point.


**************************
Engineering Infrastructure
**************************
* Version control: Git

* Build system: Makefile

* Testing framework: Google Test and pytest

* Continuous integration: Github actions


*****************
Schedule
*****************
1. Week 1-2 (9/30~):
    * Set up the development environment.
    * Familiarize with the T-IPLM model.
    * Implement the Python interface for user input.
    * Write unit tests and set up CI using GitHub Actions.

2. Week 3-4 (10/14~):
    * Implement C++ module for path loss calculation.

3. Week 5-6 (10/28~):
    * Optimize the C++ module with multithreading.
    * Integrate Python and C++ using pybind11.

4. week 7-9 (11/11~):
    * Use Matplotlib to generate 2D heatmaps for signal strength distribution.

5. week 10-11 (12/2~): 
    * Make the slides and Prepare the final report.


*****************
References
*****************
* `Realistic indoor path loss modeling for regular WiFi operations in India (T-IPLM) <https://ieeexplore.ieee.org/abstract/document/8077107>`__
 