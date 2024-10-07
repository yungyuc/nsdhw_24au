import math
import sys
import _vector

def test_same_vectors():
    # Test when the two vectors are the same, the angle should be 0 radians
    assert math.isclose(_vector.ang(1, 0, 1, 0), 0, abs_tol=1e-6)

def test_perpendicular_vectors():
    # Test when the two vectors are perpendicular, the angle should be pi/2 radians
    assert math.isclose(_vector.ang(1, 0, 0, 1), math.pi / 2, abs_tol=1e-6)

def test_opposite_vectors():
    # Test when the two vectors are in opposite directions, the angle should be pi radians
    assert math.isclose(_vector.ang(1, 0, -1, 0), math.pi, abs_tol=1e-6)

def test_arbitrary_angle():
    # Test with two arbitrary vectors that form a known angle
    assert math.isclose(_vector.ang(1, 0, math.sqrt(3)/2, 1/2), math.pi / 6, abs_tol=1e-6)
