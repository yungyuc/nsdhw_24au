from _vector import calc_angle
import math, pytest
import numpy as np

def calc_angle_(v1, v2):
    v1 = np.array(v1)
    v2 = np.array(v2)
    
    dot_product = np.dot(v1, v2)
    magnitude_v1 = np.linalg.norm(v1)
    magnitude_v2 = np.linalg.norm(v2)
    
    cos_theta = dot_product / (magnitude_v1 * magnitude_v2)
    angle = np.arccos(cos_theta)
    
    return angle  

def test_calc_angle():
    # zero angle
    a1 = calc_angle([1, 0], [1, 0])
    assert math.isclose(a1, 0)

    # 90 degree angle
    a2 = calc_angle([1, 0], [0, 1])
    assert math.isclose(a2, math.pi / 2)

    # random angle
    a3 = calc_angle([124, 331], [-22, 95])
    assert math.isclose(a3, calc_angle_([124, 331], [-22, 95]))

def test_calc_angle_error():
    # invalid input
    with pytest.raises(ValueError):
        calc_angle([0, 0], [1, 0])
