import _vector
import math

def test_calRadianAngle_zero_length():
    try:
        _vector.calRadianAngle(0,0,1,1)
        assert False
    except ValueError:
        assert True

def test_calRadianAngle_zero_angle():
    assert math.isclose(_vector.calRadianAngle(1,0,1,0), 0, rel_tol=1e-9)

def test_calRadianAngle_90_degree():
    assert math.isclose(_vector.calRadianAngle(1,0,0,1), math.pi/2, rel_tol=1e-9)
    
def test_calRadianAngle_other_degree():
    assert math.isclose(_vector.calRadianAngle(1,0,1,1), math.pi/4, rel_tol=1e-9)
    assert math.isclose(_vector.calRadianAngle(1,0,-1,1), 3*math.pi/4, rel_tol=1e-9)
    assert math.isclose(_vector.calRadianAngle(1,0,-1,0), math.pi, rel_tol=1e-9)
    assert math.isclose(_vector.calRadianAngle(1,0,-1,-1), 3*math.pi/4, rel_tol=1e-9)