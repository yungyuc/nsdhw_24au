import pytest
import math
from _vector import Vector


def test_default_constructor_should_have_correct_x_and_y():
    v = Vector()

    assert v.GetX() == 0
    assert v.GetY() == 0


def test_constructor_with_x_and_y_should_have_correct_x_and_y():
    v = Vector(3, 5)

    assert v.GetX() == 3
    assert v.GetY() == 5

def test_get_distance_with_non_zero_vector_should_have_correct_distance():
    v = Vector(3, 4)

    assert v.GetDistance() == 5


def test_get_angle_with_non_zero_vector_should_have_correct_angle():
    v = Vector(3, 0)
    other_v = Vector(0, 3)

    assert v.GetAngle(other_v) == math.pi / 2


def test_get_angle_with_zero_vector_should_throw_exception():
    v = Vector(0, 0)
    other_v = Vector(0, 3)

    try :
        v.GetAngle(other_v)
        assert False
    except:
        assert True


def test_get_angle_with_zero_other_vector_should_throw_exception():
    v = Vector(3, 0)
    other_v = Vector(0, 0)

    try :
        v.GetAngle(other_v)
        assert False
    except:
        assert True


def test_get_angle_with_the_same_vector_should_have_correct_angle():
    v = Vector(3, 0)
    other_v = Vector(3, 0)

    assert v.GetAngle(other_v) == 0


def test_get_angle_with_the_same_vector_should_have_correct_angle():
    v = Vector(3, 3)
    other_v = Vector(-4, 0)

    assert v.GetAngle(other_v) == 3 * math.pi / 4