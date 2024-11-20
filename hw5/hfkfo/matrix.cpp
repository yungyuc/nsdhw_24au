#include "matrix.hpp"
// #include <pybind11/pybind11.h>
// #include <pybind11/operators.h>


/*
 * Naive matrix matrix multiplication.
 */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i=0; i<ret.nrow(); ++i)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j)
            {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }

    return ret;
}

Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t size)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for(size_t i = 0 ; i < mat1.nrow() ; i += size)
    {
        for(size_t k = 0 ; k < mat2.ncol() ; k += size)
        {
            for(size_t j = 0; j < mat1.ncol() ; j += size)
            {
                for(size_t ti = i; ti < std::min(mat1.nrow(), i + size) ; ++ti)
                {
                    for(size_t tk = k ; tk < std::min(mat2.ncol(), k + size) ; ++tk)
                    {
                        for(size_t tj = j ; tj < std::min(mat1.ncol(), j + size) ; ++tj)
                        {
                            ret(ti, tk) += mat1(ti, tj) * mat2(tj, tk);
                        }
                    }
                }
            }
        }
    }
    return ret;
}

Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());
    
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                mat1.nrow(), mat2.ncol(), mat1.ncol(), 1.0, 
                mat1.buffer(), mat1.ncol(),  // A matrix
                mat2.buffer(), mat2.ncol(),  // B matrix
                0.0, 
                ret.buffer(), ret.ncol());  // C matrix (result)

    return ret;
}

std::ostream & operator << (std::ostream & ostr, Matrix const & mat)
{
    for (size_t i=0; i<mat.nrow(); ++i)
    {
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j)
        {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }

    return ostr;
}




// PYBIND11_MODULE(_matrix, m){
//     m.def("multiply_naive", &multiply_naive, "use naive");
//     m.def("multiply_mkl", &multiply_mkl, "use mkl");
//     m.def("multiply_tile", &multiply_tile, "use tile");
//     pybind11::class_<Matrix>(m, "Matrix")
//         .def(pybind11::init<size_t, size_t>())
//         .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> i, double val) {
//             self(i.first, i.second) = val;
//         })
//         .def("__getitem__", [](Matrix &self, std::pair<size_t, size_t> i) {
//             return self(i.first, i.second);
//         })
//         .def("__eq__", &Matrix::operator==)
//         .def_property("nrow", &Matrix::nrow, nullptr)
//         .def_property("ncol", &Matrix::ncol, nullptr);
// }