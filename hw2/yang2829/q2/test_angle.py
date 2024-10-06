import pytest
import math
import _vector

def test_zero_length():
    v1 = [0., 0.]
    v2 = [1., 0.]
    with pytest.raises(ValueError, match="vector length can not be 0"):
        _vector.cal_deg(v1, v2)

def test_zero_angle():
    v1 = [1., 1.]
    v2 = [3., 3.]
    a = _vector.cal_deg(v1, v2)
    assert math.isclose(a, 0, abs_tol=1e-4), "0 angle assert"

def test_ninety_angle():
    v1 = (1., 0.)
    v2 = (0., 1.)
    a = _vector.cal_deg(v1, v2)
    assert math.isclose(a, math.pi/2, abs_tol=1e-4), "90 angle assert"

def test_forty_five_angle():
    v1 = (1., 0.)
    v2 = (1., 1.)
    a = _vector.cal_deg(v1, v2)
    assert math.isclose(a, math.pi/4, abs_tol=1e-4), "45 angle assert"
