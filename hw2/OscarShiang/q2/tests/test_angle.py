import pytest
import math

import _vector

def test_flat():
    a = _vector.Vec(1, 0)
    b = _vector.Vec(-1, 0)

    assert math.isclose(math.pi, a.angle(b), rel_tol=1e-6)

def test_ortho():
    a = _vector.Vec(1, 0)
    b = _vector.Vec(0, 1)

    assert math.isclose(math.pi / 2, a.angle(b), rel_tol=1e-6)

def test_45_deg():
    a = _vector.Vec(1, 1)
    b = _vector.Vec(1, 0)

    assert math.isclose(math.pi / 4, a.angle(b), rel_tol=1e-6)

def test_same_angle():
    a = _vector.Vec(3, 4)
    b = _vector.Vec(0, 4)

    x = _vector.Vec(6, 8)
    y = _vector.Vec(0, 8)

    assert math.isclose(a.angle(b), x.angle(y))

def test_parallel():
    a = _vector.Vec(0, 5)
    b = _vector.Vec(0, 10)

    assert math.isclose(a.angle(b), 0)
