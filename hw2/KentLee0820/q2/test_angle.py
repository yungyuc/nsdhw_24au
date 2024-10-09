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
	x1, y1, x2, y2 = 3.0, 4.0, 5.0, 6.0
	l1_len = math.sqrt(x1 * x1 + y1 * y1)
	l2_len = math.sqrt(x2 * x2 + y2 * y2)
	
	ans = math.acos(((x1 * x2) + (y1 * y2)) / (l1_len * l2_len))
	assert math.isclose(calculate_angle(x1, y1, x2, y2), ans, rel_tol=1e-9)
