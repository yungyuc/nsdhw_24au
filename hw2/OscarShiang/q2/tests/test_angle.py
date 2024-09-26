import pytest
import math

import vec

def test_flat():
    a = vec.Vec(1, 0)
    b = vec.Vec(-1, 0)

    assert math.isclose(math.pi, a.angle(b), rel_tol=1e-6)

def test_ortho():
    a = vec.Vec(1, 0)
    b = vec.Vec(0, 1)

    assert math.isclose(math.pi / 2, a.angle(b), rel_tol=1e-6)

def test_45_deg():
    a = vec.Vec(1, 1)
    b = vec.Vec(1, 0)

    assert math.isclose(math.pi / 4, a.angle(b), rel_tol=1e-6)

def test_same_angle():
    a = vec.Vec(3, 4)
    b = vec.Vec(0, 4)

    x = vec.Vec(6, 8)
    y = vec.Vec(0, 8)

    assert math.isclose(a.angle(b), x.angle(y))

def test_parallel():
    a = vec.Vec(0, 5)
    b = vec.Vec(0, 10)

    assert math.isclose(a.angle(b), 0)
