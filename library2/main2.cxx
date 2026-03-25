#include <iostream>
#include <vector>
#include <ctime>
#include <gmpxx.h>
#include "matrix2.h"
#include "fraction2.h"

using namespace std;

void showMenu()
{
    cout << "\n========== БИБЛИОТЕКА МАТРИЦ (GMP ДРОБИ) ==========" << endl;
    cout << "1. Умножение матрицы на вектор" << endl;
    cout << "2. Классическое умножение матриц (A * B)" << endl;
    cout << "3. Блочное умножение матриц" << endl;
    cout << "4. Алгоритм Штрассена" << endl;
    cout << "5. Решение СЛАУ (Метод Гаусса)" << endl;
    cout << "6. Решение СЛАУ (Метод Жордана-Гаусса)" << endl;
    cout << "7. Обратная матрица (Метод Гаусса)" << endl;
    cout << "8. Обратная матрица (Метод Жордана-Гаусса)" << endl;
    cout << "0. Выход" << endl;
    cout << "===============================================" << endl;
    cout << "Выберите действие: ";
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true)
    {
        showMenu();
        if (!(cin >> choice))
            break;
        if (choice == 0)
            break;

        int n;
        cout << "Введите размерность квадратной матрицы (N): ";
        cin >> n;

        Matrix A(n, n);
        int fillChoice;
        cout << "Заполнить матрицу A:\n1. Вручную\n2. Случайно\nВыбор: ";
        cin >> fillChoice;

        if (fillChoice == 1)
            A.input();
        else
            A.fillRandom(10);

        A.print("Матрица A");

        switch (choice)
        {
        case 1:
        {	
            vector<Ordinary> v;
            v.reserve(n);
            cout << "Заполнение вектора v:" << endl;
          
            for (int i = 0; i < n; i++){
				if (fillChoice == 1){
					long long temp_n, temp_d;
					cout << "Элемент [" << i << "]. Введите числитель и знаменталеь: ";
					cin >> temp_n >> temp_d;
					v.push_back(Ordinary(temp_n, temp_d));
					} else {
						v.push_back (Ordinary(rand() % 10, rand() % 9 + 1));}
				
				}
                

            vector<Ordinary> resV = A.multiplyVector(v);
            cout << "Результат A * v: [ ";
            for (auto &f : resV)
                cout << f.toString() << " ";
            cout << "]" << endl;
            cout << "Результат A * v (десят.): [ ";
            for (auto &f : resV)
                cout << f.toDecimal() << " ";
            cout << "]" << endl;
            break;
        }
        case 2:
        {
            Matrix B(n, n);
            if (fillChoice == 1)
                B.input();
            else
                B.fillRandom(5);
            B.print("Матрица B");
            Matrix::multiplyClassic(A, B).print("Результат A * B (Классика)");
            Matrix::multiplyClassic(A, B).printDecimal("");
            break;
        }
        case 3:
        {
            Matrix B(n, n);
            if (fillChoice == 1)
                B.input();
            else
                B.fillRandom(5);
            Matrix::multiplyBlock(A, B, 2).print("Результат A * B (Блок)");
            Matrix::multiplyBlock(A, B, 2).printDecimal("");
            break;
        }
        case 4:
        {
            if ((n & (n - 1)) != 0)
                cout << "Ошибка: Размер должен быть степенью 2!" << endl;
            else
            {
                Matrix B(n, n);
                if (fillChoice == 1)
                    B.input();
                else
                    B.fillRandom(3);
                Matrix::strassen(A, B).print("Результат (Штрассен)");
                Matrix::strassen(A, B).printDecimal("");
            }
            break;
        }
        case 5:
        {
            vector<Ordinary> b;
            b.reserve(n);
            for (int i = 0; i < n; i++){
				if(fillChoice == 1){
					long long temp_n, temp_d;
					cout << "Элемент [" << i << "]. Введите числитель и знаменталеь: ";
					cin >> temp_n >> temp_d;
					b.push_back(Ordinary(temp_n, temp_d));
					
					}else {
						b.push_back (Ordinary(rand() % 10, rand() % 9 + 1));}
				}
            vector<Ordinary> x = Matrix::solveGauss(A, b);
            cout << "Решение x: ";
            for (auto &f : x)
                cout << f.toString() << " ";
            cout << endl;
            cout << "Решение x (десятичная форма): ";
            for (auto &f : x)
                cout << f.toDecimal() << " ";
            cout << endl;
            break;
        }
        case 6:
        {
            vector<Ordinary> b;
            b.reserve(n);
            for (int i = 0; i < n; i++){
				if(fillChoice == 1){
					long long temp_n, temp_d;
					cout << "Элемент [" << i << "]. Введите числитель и знаменталеь: ";
					cin >> temp_n >> temp_d;
					b.push_back(Ordinary(temp_n, temp_d));
					
					}else {
						b.push_back (Ordinary(rand() % 10, rand() % 9 + 1));}
				}
            vector<Ordinary> x = Matrix::solveJordanGauss(A, b);
            cout << "Решение x (Жордан): ";
            for (auto &f : x)
                cout << f.toString() << " ";
            cout << endl;
            break;
            cout << "Решение x (Жордан) (десят.): ";
            for (auto &f : x)
                cout << f.toDecimal() << " ";
            cout << endl;
            break;
        }
        case 7:
            Matrix::inverseGauss(A).print("Обратная (Гаусс)");
            Matrix::inverseGauss(A).printDecimal("");
            break;
        case 8:
            Matrix::inverseJordanGauss(A).print("Обратная (Жордан)");
            Matrix::inverseJordanGauss(A).printDecimal("");
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }

        cout << "\nНажмите Enter...";
        cin.ignore(1000, '\n');
        cin.get();
    }
    return 0;
}
