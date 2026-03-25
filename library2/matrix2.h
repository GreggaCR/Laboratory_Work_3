#ifndef MATRIX2_H
#define MATRIX2_H

#include "fraction2.h"
#include <vector>

class Matrix
{
public:
    int rows, cols;
    std::vector<std::vector<Ordinary>> data;

    Matrix(int r, int c);
    static Matrix identity(int n);

    void input();
    void print(const char *title) const;
    void printDecimal(const char *title) const;
    void fillRandom(int maxVal = 10);
    // Методы из задания
    std::vector<Ordinary> multiplyVector(const std::vector<Ordinary> &v) const;
    static Matrix multiplyClassic(const Matrix &A, const Matrix &B);
    static Matrix multiplyBlock(const Matrix &A, const Matrix &B, int blockSize = 2);
    static Matrix strassen(const Matrix &A, const Matrix &B);

    static std::vector<Ordinary> solveGauss(Matrix A, std::vector<Ordinary> b);
    static std::vector<Ordinary> solveJordanGauss(Matrix A, std::vector<Ordinary> b);

    static Matrix inverseGauss(Matrix A);
    static Matrix inverseJordanGauss(Matrix A);

    // Вспомогательные для Штрассена
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
};

#endif
