import math
import pytest
from _vector import calc_angle


def test_calc_angle1():
    # right angle
    a = calc_angle(0, 1, 1, 0)
    b = math.pi/2
    assert math.isclose(a, b, rel_tol=10e-6)

def test_calc_angle2():
    # 180 degree
    a = calc_angle(-1, 0, 1, 0)
    b = math.pi
    assert math.isclose(a, b, rel_tol=10e-6)

def test_calc_angle3():
    # 0 degree
    a = calc_angle(1, 0 , 2, 0)
    b = 0
    assert math.isclose(a, b, rel_tol=10e-6)

