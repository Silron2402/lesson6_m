#include <src/matrix.h>
#include <iostream>
using namespace std;
using namespace math;

real &Matrix::operator()(int row, int col) /// возврат по ссылке (стоит символ &)
{
    if (row > this->rows_)
    {
        std::cerr << "Matrix: row number is out of bounds" << std::endl;
        // return 0; закоменчено,т.к. возврат по ссылке
    };

    if (col > this->cols_)
    {
        std::cerr << "Matrix: col number is out of bounds" << std::endl;
        // return 0; закоменчено, т.к. возврат по ссылке
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
        // return 0; закоменчено,т.к. возвнрат по ссылке
    };

    if (col > this->cols_)
    {
        std::cerr << "Matrix: col number is out of bounds" << std::endl;
        // return 0; закоменчено, т.к. возврат по ссылке
    };

    int pos{0};

    pos = cols_ * row + col;

    return this->mvec_.at(pos); // неявный указатель this принадлежности к классу
}

// Функция, предназначенная для вывода матрицы в консоль
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

//перегрузка оператора сложения 
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

//перегрузка оператора вычитания матриц
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

//перегрузка оператора умножения
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
        int row = (int)std::floor(pos / M.cols_);
        int col = pos - row * M.cols_;

        for (int k = 0; k < A.cols_; ++k)
        {
            M.mvec_.at(pos) += A(row, k) * B(k, col);
        }
    }

    return M;
}

// Перегрузка оператора -=
Matrix &Matrix::operator+=(const Matrix &M) //& передача по ссылке, тк.к матрицы могут быть довольно большие
{
    // Проверим равенство строк и столбцов матриц. При неравенстве выдадим сообщение об ошибке и вернем исходную матрицу
    if ((this->cols_ != M.cols_) || (this->rows_ != M.rows_))
    {
        std::cerr << "Matrix: Operation += can't be  started!" << std::endl;
        return *this;
    }

    // выполним почленное сложение
    for (int i = 0; i < M.mvec_.size(); ++i)
    {
        this->mvec_.at(i) = this->mvec_.at(i) + M.mvec_.at(i);
    }

    return *this;
}

// Перегрузка оператора -=
Matrix &Matrix::operator-=(const Matrix &M) //& передача по ссылке, тк.к матрицы могут быть довольно большие
{
    // Проверим равенство строк и столбцов матриц. При неравенстве выдадим сообщение об ошибке и вернем исходную матрицу
    if ((this->cols_ != M.cols_) || (this->rows_ != M.rows_))
    {
        std::cerr << "Matrix: Operation -= can't be  started!" << std::endl;
        return *this;
    }

    // выполним почленное вычитание
    for (int i = 0; i < M.mvec_.size(); ++i)
    {
        this->mvec_.at(i) = this->mvec_.at(i) - M.mvec_.at(i);
    }

    return *this;
}

// Перегрузка оператора *=
Matrix &Matrix::operator*=(const Matrix &M) //& передача по ссылке, тк.к матрицы могут быть довольно большие
{
    // Проверим равенство строк первой матрицы и столбцов второй матрицы. При неравенстве выдадим сообщение об ошибке и вернем исходную матрицу
    if (this->cols_ != M.rows_)
    {
        std::cerr << "Matrix: Matrices can't be multiplied!" << std::endl;
        return *this;
    }

    // выполним умножение
    *this = math::operator*(*this, M);
    // возврат результата
    return *this;
}

// добавим пространство имен math
namespace math
{
    // Функция, реализующая перегрузку операции вывода
    std::ostream &operator<<(std::ostream &out, const Matrix &A)
    {

        for (int i = 0; i < A.rows_; ++i)
        {
            for (int j = 0; j < A.cols_; ++j)
            {
                out << A.mvec_.at(A.cols_ * i + j) << " ";
            }
            out << std::endl;
        }
        return out;
    }

    // Функция, реализующая перегрузку операции ввода
    std::istream &operator>>(std::istream &in, Matrix &A)
    {
        real myvar;
        std::cout << "Let's create your own matrix" << std::endl;
        // ввод числа столбцов
        std::cout << "Enter number of cols of your matrix:" << std::endl;
        in >> A.cols_;
        // ввод числа строк
        std::cout << "Enter number of rows of your matrix:" << std::endl;
        in >> A.rows_;
        
        // Ввод элементов матрицы
        std::cout << "Let's fill in the matrix A, you created" << std::endl;

        // организуем вложенные циклы для поэлементного ввода элементов
        for (int i = 0; i < A.rows_; ++i)
        {
            for (int j = 0; j < A.cols_; ++j)
            {
                std::cout << "Enter element A(" << i << " , " << j << "):" << std::endl;
                in >> myvar;
                //допишем введенный элемент в конец вектора 
                A.mvec_.push_back(myvar);
            }
        }
        return in;
    }

}