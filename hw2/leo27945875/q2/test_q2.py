import _vector
import math
import pytest


def test_45_degree():
    angle = _vector.calc_angle(1., 1., 1., 0.)
    assert abs(angle - 0.25 * math.pi) < 1e-5


def test_reverse():
    angle = _vector.calc_angle(0.3, 0.4, -0.3, -0.4)
    assert abs(angle - math.pi) < 1e-5


def test_orthogonal():
    angle = _vector.calc_angle(0., 1., 1., 0.)
    assert abs(angle - 0.5 * math.pi) < 1e-5


def test_parallel():
    angle = _vector.calc_angle(1., 1., 0.5, 0.5)
    assert abs(angle) < 1e-5


def test_error():
    with pytest.raises(ValueError):
        angle = _vector.calc_angle(1., 1., 0., 0.)