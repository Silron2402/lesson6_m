#pragma once
#include <vector>
#include <iostream>
using namespace std;


namespace math
{
    typedef double real;

    class Matrix
    {
    private:
        int cols_;
        int rows_;
        std::vector<real> mvec_;

    public:
        Matrix() {};

        Matrix(int cols, int rows) : cols_(cols), rows_(rows), mvec_(std::vector<real>(cols * rows)) {};

        real& operator()(int row, int col); // возврат значения по ссылке (знак &)

        real operator()(int row, int col) const;

        void print();

        //Перегрузка операции сложения 
        friend Matrix operator+(const Matrix &A, const Matrix &B);

        //Перегрузка операции вычитания 
        friend Matrix operator-(const Matrix &A, const Matrix &B);

        //Перегрузка операции умножения 
        friend Matrix operator*(const Matrix &A, const Matrix &B);

        Matrix& operator+=(const Matrix &B);

        Matrix& operator-=(const Matrix &B);

        // перегрузка операции вывода
        friend std::ostream &operator<<(std::ostream &out, const Matrix &A);
    };
}