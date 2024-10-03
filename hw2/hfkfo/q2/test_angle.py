import math
from _vector import angle_cal

import pytest

def test_zero_length_2_vector():
    assert math.isnan(angle_cal(0.0, 0.0, 0.0, 0.0))

def test_zero_angle():
    assert math.isclose(angle_cal(1.0, 0.0, 2.0, 0.0), 0)

def test_right_angle():
    assert math.isclose(round(angle_cal(1.0, 0.0, 0.0, 2.0), 2), round(math.pi * 0.5, 2))

def test_one_other_angle():
    assert math.isclose(round(angle_cal(1.0, 0.0, -1.0, 0.0), 2), round(math.pi, 2))