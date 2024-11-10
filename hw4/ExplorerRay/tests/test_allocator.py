import _matrix
from utils import generate_matrix_2d

def test_basic_bytes():
    assert 0 == _matrix.bytes()
    assert 0 == _matrix.allocated()
    assert 0 == _matrix.deallocated()
    assert _matrix.bytes() == _matrix.allocated() - _matrix.deallocated()

def test_basic_allocate():
    sz = 20
    generate_matrix_2d(sz, sz)
    assert (sz*sz*8) == _matrix.allocated()
    assert _matrix.bytes() == _matrix.allocated() - _matrix.deallocated()
