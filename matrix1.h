#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <cassert>
#include <functional>
#include <iostream>
#include <utility>
using namespace std;

template <typename T>
void PrintMatrix4(T &n, ostream &os) { os << n << " "; }

template <typename T>
class Matrix1 {
    private:
        T      **m_pMat = nullptr;
        size_t   m_rows = 0, m_cols = 0;
    public:
        Matrix1()      { }
        Matrix1(size_t rows, size_t cols);

        Matrix1(const Matrix1 &other); // Copy constructor
        Matrix1(Matrix1 &&other);      // Move constructor

        ~Matrix1()     { Destroy(); }

        Matrix1 &operator=(const Matrix1 &other);
        Matrix1 &operator=(Matrix1 &&other);
        
        T* operator[](size_t row);
        const T* operator[](size_t row) const;

        T Get(size_t row, size_t col) const;
        void Set(size_t row, size_t col, T value);

        size_t Rows() const;
        size_t Cols() const;
        
        void     Create();
        istream &Read(istream &is);
        template <typename Func, typename... Args>
        void ApplyFunctionToAll(Func func, Args&& ...args);
        ostream &Print(ostream &os);
        void Destroy();
        
        //Matrix1(const Matrix1 &other);
        //Matrix1 &operator=(const Matrix1 &other);
        //Matrix1 &operator=(Matrix1 &&other);
        Matrix1 operator+(const Matrix1 &other) const;
        Matrix1 operator-(const Matrix1 &other) const;
        Matrix1 operator*(const Matrix1 &other) const;
        Matrix1 operator*(T value) const;
        
};
template <typename T>
Matrix1<T>::Matrix1(size_t rows, size_t cols) {
    m_rows = rows;
    m_cols = cols;
    Create();

    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_cols; ++j)
            m_pMat[i][j] = 0;
}

template <typename T>
T* Matrix1<T>::operator[](size_t row) {
    assert(row < m_rows);
    return m_pMat[row];
}

template <typename T>
const T* Matrix1<T>::operator[](size_t row) const {
    assert(row < m_rows);
    return m_pMat[row];
}

template <typename T>
T Matrix1<T>::Get(size_t row, size_t col) const {
    assert(row < m_rows && col < m_cols);
    return m_pMat[row][col];
}

template <typename T>
void Matrix1<T>::Set(size_t row, size_t col, T value) {
    assert(row < m_rows && col < m_cols);
    m_pMat[row][col] = value;
}

template <typename T>
size_t Matrix1<T>::Rows() const {
    return m_rows;
}

template <typename T>
size_t Matrix1<T>::Cols() const {
    return m_cols;
}
template <typename T>
void Matrix1<T>::Create() {
    assert(m_rows > 0 && m_cols > 0);
    m_pMat = new T *[m_rows];
    for(size_t i = 0 ; i < m_rows ; ++i)
        m_pMat[i] = new T[m_cols];
}

template <typename T>
Matrix1<T>::Matrix1(Matrix1 &&other) {
    m_pMat = exchange(other.m_pMat, nullptr);
    m_rows = exchange(other.m_rows, 0);
    m_cols = exchange(other.m_cols, 0);
}

template <typename T>
istream &Matrix1<T>::Read(istream &is) {
    Destroy();
    is >> m_rows >> m_cols;
    Create();
    for(size_t i = 0 ; i < m_rows ; ++i)
        for(size_t j = 0 ; j < m_cols ; ++j)
            is >> m_pMat[i][j];
    return is;
}

template <typename T>
ostream &Matrix1<T>::Print(ostream &os) {
    for(size_t i = 0 ; i < m_rows ; ++i) {
        for(size_t j = 0 ; j < m_cols ; ++j)
            os << m_pMat[i][j] << " ";
        os << endl;
    }
    return os;
}

template <typename T>
void Matrix1<T>::Destroy() {
    if(m_pMat != nullptr) {
        for(size_t i = 0 ; i < m_rows ; ++i)
            delete[] m_pMat[i];
        delete[] m_pMat;
        m_pMat = nullptr;
    }
    m_rows = 0;
    m_cols = 0;
}

template <typename T>
template <typename Func, typename... Args>
void Matrix1<T>::ApplyFunctionToAll(Func func, Args&& ...args) {
    for(size_t i = 0 ; i < m_rows ; ++i)
        for(size_t j = 0 ; j < m_cols ; ++j)
            func(m_pMat[i][j], args...);
}

template <typename T>
Matrix1<T>::Matrix1(const Matrix1 &other) {
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    if(m_rows > 0 && m_cols > 0) {
        Create();
        for(size_t i = 0; i < m_rows; ++i)
            for(size_t j = 0; j < m_cols; ++j)
                m_pMat[i][j] = other.m_pMat[i][j];
    } else {
        m_pMat = nullptr;
    }
}

template <typename T>
Matrix1<T> &Matrix1<T>::operator=(const Matrix1 &other) {
    if(this != &other) {
        Destroy();
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        if(m_rows > 0 && m_cols > 0) {
            Create();
            for(size_t i = 0; i < m_rows; ++i)
                for(size_t j = 0; j < m_cols; ++j)
                    m_pMat[i][j] = other.m_pMat[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix1<T> &Matrix1<T>::operator=(Matrix1 &&other) {
    if(this != &other) {
        Destroy();
        m_pMat = exchange(other.m_pMat, nullptr);
        m_rows = exchange(other.m_rows, 0);
        m_cols = exchange(other.m_cols, 0);
    }
    return *this;
}

template <typename T>
Matrix1<T> Matrix1<T>::operator+(const Matrix1 &other) const {
    assert(m_rows == other.m_rows && m_cols == other.m_cols);
    Matrix1<T> res;
    res.m_rows = m_rows;
    res.m_cols = m_cols;
    res.Create();
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_cols; ++j)
            res.m_pMat[i][j] = m_pMat[i][j] + other.m_pMat[i][j];
    return res;
}

template <typename T>
Matrix1<T> Matrix1<T>::operator-(const Matrix1 &other) const {
    assert(m_rows == other.m_rows && m_cols == other.m_cols);
    Matrix1<T> res;
    res.m_rows = m_rows;
    res.m_cols = m_cols;
    res.Create();
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_cols; ++j)
            res.m_pMat[i][j] = m_pMat[i][j] - other.m_pMat[i][j];
    return res;
}

template <typename T>
Matrix1<T> Matrix1<T>::operator*(const Matrix1 &other) const {
    assert(m_cols == other.m_rows);
    Matrix1<T> res;
    res.m_rows = m_rows;
    res.m_cols = other.m_cols;
    res.Create();
    for(size_t i = 0; i < m_rows; ++i) {
        for(size_t j = 0; j < other.m_cols; ++j) {
            res.m_pMat[i][j] = 0;
            for(size_t k = 0; k < m_cols; ++k)
                res.m_pMat[i][j] += m_pMat[i][k] * other.m_pMat[k][j];
        }
    }
    return res;
}

template <typename T>
Matrix1<T> Matrix1<T>::operator*(T value) const {
    Matrix1<T> res;
    res.m_rows = m_rows;
    res.m_cols = m_cols;
    res.Create();
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_cols; ++j)
            res.m_pMat[i][j] = m_pMat[i][j] * value;
    return res;
}

template <typename T>
Matrix1<T> operator*(T val, const Matrix1<T> &m) {
    return m * val;
}

template <typename T>
istream &operator>>(istream &is, Matrix1<T> &mat) {
    return mat.Read(is);
}

template <typename T>
ostream &operator<<(ostream &os, Matrix1<T> &mat) {
    return mat.Print(os);
}

#endif