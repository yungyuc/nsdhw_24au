import math
import pytest
from _vector import calculate_angle

# Test zero angle (both vectors pointing in the same direction)
def test_zero_angle():
    assert math.isclose(calculate_angle(1, 0, 2, 0), 0, rel_tol=1e-9)

# Test right angle (90 degrees)
def test_right_angle():
    assert math.isclose(calculate_angle(1, 0, 0, 1), math.pi / 2, rel_tol=1e-9)

# Test opposite vectors (180 degrees)
def test_opposite_vectors():
    assert math.isclose(calculate_angle(1, 0, -1, 0), math.pi, rel_tol=1e-9)

# Test arbitrary angle
def test_arbitrary_angle():
    angle = calculate_angle(1, 1, 0, 1)
    assert math.isclose(angle, math.pi / 4, rel_tol=1e-9)

# Test invalid vectors (one of them has zero length)
def test_zero_length_vector():
    with pytest.raises(ValueError):
        calculate_angle(0, 0, 1, 0)

if __name__ == "__main__":
    pytest.main()
