#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <limits>
#include <stdio.h>
#include <random>

using namespace std;

class Matrix{
public:
    Matrix(size_t row , size_t col): m_row(row), m_col(col){
        reset_buffer(row, col);
    }
    
    Matrix(size_t row , size_t col , vector<double> vec){
        reset_buffer(row, col);
        (*this) = vec;
    }
    
    ~Matrix(){
        delete[] m_buffer;
    }
    
    Matrix & operator=(const std::vector<double> & vec) {
        if (vec.size() != m_row * m_col) {
            throw std::out_of_range("operator=(): vector size differs from matrix size");
        }
        std::copy(vec.begin(), vec.end(), m_buffer);
        return *this;
    }
    double& operator()(size_t i, size_t j) {
        return m_buffer[i * m_col + j];
    }

    size_t nrow() const {return m_row;}
    size_t ncol() const {return m_col;}
    double* data() {
        return m_buffer;
    }

    const double* data() const {
        return m_buffer;
    }

    
private:
    size_t m_row , m_col;
    double * m_buffer = nullptr;
    void reset_buffer(size_t row, size_t col)
    {
        if (m_buffer) { delete[] m_buffer; }
        const size_t nelement = row * col;
        if (nelement) { m_buffer = new double[nelement]; }
        else { m_buffer = nullptr; }
        m_row = row;
        m_col = col;
    }
};
