import pytest
import math
import _vector

def test_zero_angle():
    v1 = [1, 0]
    v2 = [1, 0]
    assert abs(_vector.angle(v1, v2) - math.pi*0) < 1e-6

def test_half_right_angle():
    v1 = [1, 1]
    v2 = [1, 0]
    assert abs(_vector.angle(v1, v2) - math.pi*1/4) < 1e-6

def test_right_angle():
    v1 = [0, 1]
    v2 = [1, 0]
    assert abs(_vector.angle(v1, v2) - math.pi*1/2) < 1e-6

def test_double_right_angle():
    v1 = [-1, 0]
    v2 = [1, 0]
    assert abs(_vector.angle(v1, v2) - math.pi) < 1e-6

def test_error_input():
    v1 = [0, 0]
    v2 = [1, 0]
    with pytest.raises(ValueError):
        _vector.angle(v1, v2)

