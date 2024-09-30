import _vector
import math


def test_calc_angle():
    angle = _vector.calc_angle(0., 1., 1., 0.)
    assert abs(angle - 0.5 * math.pi) < 1e-5