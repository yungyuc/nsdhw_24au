import pytest
import math
import random
from _vector import calculate_angle


def test_zero_length():
	assert math.isnan(calculate_angle(0, 0, 0, 0))


def test_zero_angle():
	assert math.isclose(calculate_angle(1, 0, 2, 0), 0, abs_tol = 0.001)


def test_perpencular_angle():
	assert math.isclose(calculate_angle(2, 1, 1, -2), math.pi / 2, abs_tol=1e-9, rel_tol=1e-9)


def test_any_angle():
	x1, y1, x2, y2 = random.random(), random.random(), random.random(), random.random()
	ans = math.atan2(y2, x2) - math.atan2(y1, x1)
	ans = math.pi * 2 + ans if ans < 0 else math.pi * 2 - ans if ans > math.pi else ans 
	assert math.isclose(calculate_angle(x1, y1, x2, y2), ans, rel_tol=1e-9)
