from _vector import calc_angle
import math, pytest

def test_calc_angle():
    # zero angle
    a1 = calc_angle([1, 0], [1, 0])
    assert math.isclose(a1, 0)

    # 90 degree angle
    a2 = calc_angle([1, 0], [0, 1])
    assert math.isclose(a2, math.pi / 2)

    # 180 degree angle
    a3 = calc_angle([1, 0], [-1, 0])
    assert math.isclose(a3, math.pi)

def test_calc_angle_error():
    # invalid input
    with pytest.raises(ValueError):
        calc_angle([1, 0], [])

    with pytest.raises(ValueError):
        calc_angle([], [])
