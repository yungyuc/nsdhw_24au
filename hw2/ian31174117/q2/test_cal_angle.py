import pytest
import numpy as np
from _vector import cal_angle_between_vec

def test_cal_angle_between_vec():
    vec1 = np.array([1,0])
    vec2 = np.array([0,1])
    assert np.allclose(cal_angle_between_vec(vec1, vec2), np.pi/2)

def test_invalid_input_len():
    vec1 = np.array([1])
    vec2 = np.array([0,1])
    with pytest.raises(ValueError):
        cal_angle_between_vec(vec1, vec2)

def test_same_vec_0_rad():
    vec1 = np.array([1,0])
    vec2 = np.array([1,0])
    assert np.allclose(cal_angle_between_vec(vec1, vec2), 0)