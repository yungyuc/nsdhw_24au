import pytest
import math
import _vector

class TestAngleBetweenVectors:
    def test_invalud_value(self):
        cases = [
            ((0, 0), (1, 0)),
            ((1, 0), (0, 0)),
            ((0, 0), (0, 0))
        ]
        for v1, v2 in cases:
            with pytest.raises(ValueError, match="Error: One of the vectors has zero magnitude."):
                _ = _vector.angleBetweenVectors(v1, v2)

    def test_parallel(self):
        v1 = (1, 1)
        v2 = (2, 2)
        angle = _vector.angleBetweenVectors(v1, v2)
        assert math.isclose(angle, 0, abs_tol=1e-4), "Angle between two parallel vectors should be close to 0."

    def test_orthogonal(self):
        v1 = (1, 0)
        v2 = (0, -1)
        angle = _vector.angleBetweenVectors(v1, v2)
        assert math.isclose(angle, math.pi/2, abs_tol=1e-4), "Angle between two orthogonal vectors should be close to pi/2."

    def test_45_degree(self):
        v1 = (1, 0)
        v2 = (1, 1)
        angle = _vector.angleBetweenVectors(v1, v2)
        assert math.isclose(angle, math.pi/4, abs_tol=1e-4), "Angle between two 45-degree vectors should be close to pi/4." 

    def test_random(self):
        v1 = (1, 2)
        v2 = (3, 4)
        angle = _vector.angleBetweenVectors(v1, v2)
        assert math.isclose(angle, 0.1798535, abs_tol=1e-4), "Angle between two random vectors should be close to 0.1798535."