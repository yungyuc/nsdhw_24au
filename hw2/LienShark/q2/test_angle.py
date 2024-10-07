#!/usr/bin/env python3
import math
import pytest
from _vector import radian 

def test_zero_vector():
    x = (0.0 , 0.0)
    y = (0.0 , 0.0)
    assert math.isnan(radian(x , y))

def test_2():
    x = (1.0 , 0.0)
    y = (1.0 , 0.0)
    assert abs(pyAngle(x , y) - radian(x , y)) < 1e-3

def test_3():
    x = (1.0 , 0.0)
    y = (0.0 , 1.0)
    assert abs(pyAngle(x , y) - radian(x , y)) < 1e-3

def test_4():
    x = (1.0 , 0.0)
    y = (1.0 , 1.0)
    assert abs(pyAngle(x , y) - radian(x , y)) < 1e-3

def pyAngle(v1, v2):
    pyDot = v1[0] * v2[0] + v1[1] * v2[1]
    pyDist_A = math.sqrt(v1[0] ** 2 + v1[1] ** 2)
    pyDist_B = math.sqrt(v2[0] ** 2 + v2[1] ** 2)

    if (pyDist_A == 0 or pyDist_B == 0):
        return NAN

    pyAngle = math.acos(pyDot / (pyDist_A * pyDist_B))
    return pyAngle

if _＿name__ == '__main__':
    pytest.main()
