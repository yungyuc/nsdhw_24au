import pytest
import calculate_angle
import math
import random

def getAns(p1, p2):
    dot = p1[0] * p2[0] + p1[1] * p2[1]
    p1_len = math.sqrt(p1[0] ** 2 + p1[1] ** 2)
    p2_len = math.sqrt(p2[0] ** 2 + p2[1] ** 2)
    return math.acos(dot / (p1_len * p2_len))

def test_answer():
    TEST_NUM = 10
    for i in range(TEST_NUM):
        p1 = (random.uniform(-10, 10), random.uniform(-10, 10))
        p2 = (random.uniform(-10, 10), random.uniform(-10, 10))
        
        # p1 = (random.random()*10, random.random()*10)
        # p2 = (random.random()*10, random.random()*10)
        # p1 = (1, 0)
        # p2 = (0, 1)
        assert calculate_angle.calculate_angle(p1, p2) == pytest.approx(getAns(p1, p2))