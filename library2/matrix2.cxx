#include "matrix2.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <gmpxx.h>

using namespace std;

// Конструктор
Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, vector<Ordinary>(c, Ordinary(0, 1))) {}

// Единичная матрица
Matrix Matrix::identity(int n)
{
    Matrix res(n, n);
    for (int i = 0; i < n; i++)
        res.data[i][i] = Ordinary(1, 1);
    return res;
}

// Ввод данных
void Matrix::input()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            cout << "[" << i << "][" << j << "] ";
            data[i][j].input();
        }
}

// Генерация случайных дробей
void Matrix::fillRandom(int maxVal)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            long long n = (rand() % (maxVal * 2)) - maxVal;
            long long d = (rand() % maxVal) + 1;
            data[i][j] = Ordinary(n, d);
        }
    }
}

// Красивый вывод с выравниванием по столбцам
void Matrix::print(const char *title) const
{
    cout << "\n--- " << title << " ---" << endl;

    // Находим максимальную длину строки для выравнивания
    size_t maxWidth = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            maxWidth = max(maxWidth, data[i][j].toString().length());
        }
    }

    for (int i = 0; i < rows; i++)
    {
        cout << "| ";
        for (int j = 0; j < cols; j++)
        {
            cout << setw(maxWidth) << data[i][j].toString() << " ";
        }
        cout << "|" << endl;
    }
}

void Matrix::printDecimal(const char *title) const{
	cout<< "\n " << title << "(десятичная форма)"<< endl;
	    size_t maxWidth = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            maxWidth = max(maxWidth, data[i][j].toString().length());
        }
    }

    for (int i = 0; i < rows; i++)
    {
        cout << "| ";
        for (int j = 0; j < cols; j++)
        {
            cout << setw(maxWidth) << fixed << setprecision(4) << data[i][j].toDecimal()<< " ";
        }
        cout << "|" << endl;
    }
}

// Умножение на вектор
vector<Ordinary> Matrix::multiplyVector(const vector<Ordinary> &v) const
{
    vector<Ordinary> res(rows, Ordinary(0, 1));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i] = res[i] + (data[i][j] * v[j]);
    return res;
}

// Классическое умножение матриц
Matrix Matrix::multiplyClassic(const Matrix &A, const Matrix &B)
{
    Matrix C(A.rows, B.cols);
    for (int i = 0; i < A.rows; i++)
        for (int j = 0; j < B.cols; j++)
            for (int k = 0; k < A.cols; k++)
                C.data[i][j] = C.data[i][j] + (A.data[i][k] * B.data[k][j]);
    return C;
}

// Блочное умножение
Matrix Matrix::multiplyBlock(const Matrix &A, const Matrix &B, int blockSize)
{
    Matrix C(A.rows, B.cols);
    for (int bi = 0; bi < A.rows; bi += blockSize)
        for (int bj = 0; bj < B.cols; bj += blockSize)
            for (int bk = 0; bk < A.cols; bk += blockSize)
                for (int i = bi; i < min(bi + blockSize, A.rows); i++)
                    for (int j = bj; j < min(bj + blockSize, B.cols); j++)
                        for (int k = bk; k < min(bk + blockSize, A.cols); k++)
                            C.data[i][j] = C.data[i][j] + (A.data[i][k] * B.data[k][j]);
    return C;
}

// Алгоритм Штрассена
Matrix Matrix::strassen(const Matrix &A, const Matrix &B)
{
    int n = A.rows;
    if (n <= 2)
        return multiplyClassic(A, B);
    int k = n / 2;
    Matrix A11(k, k), A12(k, k), A21(k, k), A22(k, k), B11(k, k), B12(k, k), B21(k, k), B22(k, k);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11.data[i][j] = A.data[i][j];
            A12.data[i][j] = A.data[i][j + k];
            A21.data[i][j] = A.data[i + k][j];
            A22.data[i][j] = A.data[i + k][j + k];
            B11.data[i][j] = B.data[i][j];
            B12.data[i][j] = B.data[i][j + k];
            B21.data[i][j] = B.data[i + k][j];
            B22.data[i][j] = B.data[i + k][j + k];
        }
    }
    Matrix P1 = strassen(A11, B12 - B22);
    Matrix P2 = strassen(A11 + A12, B22);
    Matrix P3 = strassen(A21 + A22, B11);
    Matrix P4 = strassen(A22, B21 - B11);
    Matrix P5 = strassen(A11 + A22, B11 + B22);
    Matrix P6 = strassen(A12 - A22, B21 + B22);
    Matrix P7 = strassen(A11 - A21, B11 + B12);

    Matrix C11 = P5 + P4 - P2 + P6;
    Matrix C12 = P1 + P2;
    Matrix C21 = P3 + P4;
    Matrix C22 = P5 + P1 - P3 - P7;

    Matrix res(n, n);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            res.data[i][j] = C11.data[i][j];
            res.data[i][j + k] = C12.data[i][j];
            res.data[i + k][j] = C21.data[i][j];
            res.data[i + k][j + k] = C22.data[i][j];
        }
    }
    return res;
}

// СЛАУ: Метод Гаусса
vector<Ordinary> Matrix::solveGauss(Matrix A, vector<Ordinary> b)
{
    int n = A.rows;
    for (int i = 0; i < n; i++)
    {
        int maxR = i;
        for (int k = i + 1; k < n; k++)
            if (abs(A.data[k][i].toDecimal()) > abs(A.data[maxR][i].toDecimal()))
                maxR = k;
        swap(A.data[i], A.data[maxR]);
        swap(b[i], b[maxR]);
        for (int k = i + 1; k < n; k++)
        {
            Ordinary f = A.data[k][i] / A.data[i][i];
            for (int j = i; j < n; j++)
                A.data[k][j] = A.data[k][j] - (f * A.data[i][j]);
            b[k] = b[k] - (f * b[i]);
        }
    }
    vector<Ordinary> x(n, Ordinary(0, 1));
    for (int i = n - 1; i >= 0; i--)
    {
        Ordinary s(0, 1);
        for (int j = i + 1; j < n; j++)
            s = s + (A.data[i][j] * x[j]);
        x[i] = (b[i] - s) / A.data[i][i];
    }
    return x;
}

// СЛАУ: Метод Жордана-Гаусса
vector<Ordinary> Matrix::solveJordanGauss(Matrix A, vector<Ordinary> b)
{
    int n = A.rows;
    for (int i = 0; i < n; i++)
    {
        Ordinary pivot = A.data[i][i];
        for (int j = i; j < n; j++)
            A.data[i][j] = A.data[i][j] / pivot;
        b[i] = b[i] / pivot;
        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                Ordinary f = A.data[k][i];
                for (int j = i; j < n; j++)
                    A.data[k][j] = A.data[k][j] - (f * A.data[i][j]);
                b[k] = b[k] - (f * b[i]);
            }
        }
    }
    return b;
}

// Обратная матрица (Гаусс)
Matrix Matrix::inverseGauss(Matrix A)
{
    int n = A.rows;
    Matrix res = Matrix::identity(n);
    for (int i = 0; i < n; i++)
    {
        Ordinary f = A.data[i][i];
        for (int j = 0; j < n; j++)
        {
            A.data[i][j] = A.data[i][j] / f;
            res.data[i][j] = res.data[i][j] / f;
        }
        for (int k = i + 1; k < n; k++)
        {
            Ordinary f2 = A.data[k][i];
            for (int j = 0; j < n; j++)
            {
                A.data[k][j] = A.data[k][j] - (f2 * A.data[i][j]);
                res.data[k][j] = res.data[k][j] - (f2 * res.data[i][j]);
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        for (int k = i - 1; k >= 0; k--)
        {
            Ordinary f = A.data[k][i];
            for (int j = 0; j < n; j++)
            {
                A.data[k][j] = A.data[k][j] - (f * A.data[i][j]);
                res.data[k][j] = res.data[k][j] - (f * res.data[i][j]);
            }
        }
    }
    return res;
}

// Обратная матрица (Жордан-Гаусс)
Matrix Matrix::inverseJordanGauss(Matrix A)
{
    int n = A.rows;
    Matrix res = Matrix::identity(n);
    for (int i = 0; i < n; i++)
    {
        Ordinary p = A.data[i][i];
        for (int j = 0; j < n; j++)
        {
            A.data[i][j] = A.data[i][j] / p;
            res.data[i][j] = res.data[i][j] / p;
        }
        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                Ordinary f = A.data[k][i];
                for (int j = 0; j < n; j++)
                {
                    A.data[k][j] = A.data[k][j] - (f * A.data[i][j]);
                    res.data[k][j] = res.data[k][j] - (f * res.data[i][j]);
                }
            }
        }
    }
    return res;
}

// Операторы сложения и вычитания для матриц
Matrix Matrix::operator+(const Matrix &other) const
{
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res.data[i][j] = data[i][j] + other.data[i][j];
    return res;
}
Matrix Matrix::operator-(const Matrix &other) const
{
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res.data[i][j] = data[i][j] - other.data[i][j];
    return res;
}
