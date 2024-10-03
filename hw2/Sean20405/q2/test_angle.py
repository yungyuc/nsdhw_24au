import pytest
import _vector
import math
import random

def getAns(p1, p2):
    dot = p1[0] * p2[0] + p1[1] * p2[1]
    p1_len = math.sqrt(p1[0] ** 2 + p1[1] ** 2)
    p2_len = math.sqrt(p2[0] ** 2 + p2[1] ** 2)
    return math.acos(dot / (p1_len * p2_len))

def test_invalid_input():
    p1 = (0, 0)
    p2 = (0, 0)
    with pytest.raises(ValueError):
        _vector.calculateAngle(p1, p2)

def test_zero_angle():
    p1 = (1, 0)
    p2 = (1, 0)
    assert _vector.calculateAngle(p1, p2) == pytest.approx(0)

def test_right_angle():
    p1 = (1, 0)
    p2 = (0, 1)
    assert _vector.calculateAngle(p1, p2) == pytest.approx(math.pi / 2)

def test_random_angle():
    TEST_NUM = 10
    for i in range(TEST_NUM):
        p1 = (random.uniform(-10, 10), random.uniform(-10, 10))
        p2 = (random.uniform(-10, 10), random.uniform(-10, 10))
        
        # p1 = (random.random()*10, random.random()*10)
        # p2 = (random.random()*10, random.random()*10)
        # p1 = (1, 0)
        # p2 = (0, 1)
        assert _vector.calculateAngle(p1, p2) == pytest.approx(getAns(p1, p2))