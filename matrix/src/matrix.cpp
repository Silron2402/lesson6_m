#include <src/matrix.h>
#include <iostream>
using namespace std;
using namespace math;

real& Matrix::operator()(int row, int col) ///возврат по ссылке (стоит символ &)
{
    if (row > this->rows_)
    {
        std::cerr << "Matrix: row number is out of bounds" << std::endl;
        //return 0; закоменчено,т.к. возвнрат по ссылке
    };

    if (col > this->cols_)
    {
        std::cerr << "Matrix: col number is out of bounds" << std::endl;
        //return 0; закоменчено, т.к. возврат по ссылке 
    };

    int pos{0};

    pos = cols_ * row + col;

    return this->mvec_.at(pos); // неявный указатель this принадлежности к классу
}

real Matrix::operator()(int row, int col) const
{
    if (row > this->rows_)
    {
        std::cerr << "Matrix: row number is out of bounds" << std::endl;
        //return 0; закоменчено,т.к. возвнрат по ссылке
    };

    if (col > this->cols_)
    {
        std::cerr << "Matrix: col number is out of bounds" << std::endl;
        //return 0; закоменчено, т.к. возврат по ссылке 
    };

    int pos{0};

    pos = cols_ * row + col;

    return this->mvec_.at(pos); // неявный указатель this принадлежности к классу
}

void Matrix::print()
{
    for (int i = 0; i < this->rows_; ++i)
    {
        for (int j = 0; j < this->cols_; ++j)
        {
            std::cout << this->mvec_.at(cols_ * i + j) << " ";
        }
        std::cout << std::endl;
    }
};

Matrix math::operator+(const Matrix &A, const Matrix &B) //& передача по ссылке, тк.к матрицы могут быть довольно большие
{
    if ((A.cols_ != B.cols_) || (A.rows_ != B.rows_))
    {
        std::cerr << "Matrix: Matrices can't be  added!" << std::endl;
        return Matrix(0, 0);
    }

    Matrix M(A.cols_, A.rows_);
    for (int i = 0; i < M.mvec_.size(); ++i)
    {
        M.mvec_.at(i) = A.mvec_.at(i) + B.mvec_.at(i);
    }

    return M;
}

Matrix math::operator-(const Matrix &A, const Matrix &B) //& передача по ссылке, тк.к матрицы могут быть довольно большие
{
    if ((A.cols_ != B.cols_) || (A.rows_ != B.rows_))
    {
        std::cerr << "Matrix: Matrices can't be substracted!" << std::endl;
        return Matrix(0, 0);
    }

    Matrix M(A.cols_, A.rows_);
    for (int i = 0; i < M.mvec_.size(); ++i)
    {
        M.mvec_.at(i) = A.mvec_.at(i) - B.mvec_.at(i);
    }

    return M;    
}

Matrix math::operator*(const Matrix &A, const Matrix &B) //& передача по ссылке, тк.к матрицы могут быть довольно большие
{
    if (A.cols_ != B.rows_)
    {
        std::cerr << "Matrix: Matrices can't be multiplied!" << std::endl;
        return Matrix(0, 0);
    }

    Matrix M(A.rows_, B.cols_);
    for (int pos = 0; pos < M.mvec_.size(); ++pos)
    {
        int row =(int)std::floor(pos/M.cols_);
        int col = pos - row*M.cols_;

        for (int k = 0; k < A.cols_; ++k)
        {
            M.mvec_.at(pos) += A(row,k) * B(k, col);
        }

    }

    return M;   

}

Matrix& Matrix::operator+=(const Matrix& M) //& передача по ссылке, тк.к матрицы могут быть довольно большие
{
    if ((this->cols_ != M.cols_) || (this->rows_ != M.rows_))
    {
        std::cerr << "Matrix: Operation += can't be  started!" << std::endl;
        return *this;
    }

    for (int i = 0; i < M.mvec_.size(); ++i)
    {
        this->mvec_.at(i) = this->mvec_.at(i) + M.mvec_.at(i);
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& M) //& передача по ссылке, тк.к матрицы могут быть довольно большие
{
    if ((this->cols_ != M.cols_) || (this->rows_ != M.rows_))
    {
        std::cerr << "Matrix: Operation -= can't be  started!" << std::endl;
        return *this;
    }

    //Matrix M1(M.cols_, M.rows_);
    for (int i = 0; i < M.mvec_.size(); ++i)
    {
        this->mvec_.at(i) = this->mvec_.at(i) - M.mvec_.at(i);
    }

    return *this;
}

// Функция, реализующая перегрузку операции вывода
std::ostream &operator<<(std::ostream &out, const Matrix &M)
{

    for (int i = 0; i < M.rows_; ++i)
    {
        for (int j = 0; j < M.cols_; ++j)
        {
            out << M.mvec_.at(M.cols_ * i + j) << " ";
        }
        out << std::endl;
    }
    return out;
}