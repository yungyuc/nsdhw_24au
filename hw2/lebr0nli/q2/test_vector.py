import math

import pytest
from _vector import calculate_angle


def test_calculate_angle_result():
    assert math.isclose(calculate_angle([1, 0], [0, 1]), math.pi / 2, rel_tol=1e-9)

    assert math.isclose(calculate_angle([1, 0], [1, 0]), 0.0, rel_tol=1e-9)

    assert math.isclose(calculate_angle([1, 0], [-1, 0]), math.pi, rel_tol=1e-9)

    assert math.isclose(calculate_angle([1, 1], [1, 0]), math.pi / 4, rel_tol=1e-9)


def test_calculate_angle_handle_wrong_type():
    with pytest.raises(TypeError):
        calculate_angle([1, 0], 1)

    with pytest.raises(TypeError):
        calculate_angle(1, [1, 0])


def test_calculate_angle_handle_wrong_size():
    with pytest.raises(ValueError):
        calculate_angle([1, 0], [1, 0, 1])

    with pytest.raises(ValueError):
        calculate_angle([], [1, 0])
