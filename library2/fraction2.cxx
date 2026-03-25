#include "fraction2.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <gmpxx.h>
using namespace std;

Ordinary::Ordinary()
{

    mpq_init(val);
    mpq_set_si(val, 0, 1);
    mpq_canonicalize(val);
}

void Ordinary::input()
{
    long long n, d;

    cout << "Введите числитель и знаменатель: ";
    cin >> n >> d;

    if (d == 0)
        d = 1;
    mpq_set_si(val, n, d);

    mpq_canonicalize(val);
}

Ordinary::Ordinary(long long n, long long d)
{
    mpq_init(val);
    if (d == 0)
        d = 1; // Защита от деления на 0
    
    mpq_set_si(val, n, d);
    mpq_canonicalize(val);
}

Ordinary::Ordinary(const Ordinary &other)
{

    mpq_init(val);

    mpq_set(val, other.val);
    
}

Ordinary::~Ordinary()
{
    mpq_clear(val);
}

Ordinary Ordinary::operator=(const Ordinary &other)
{
    if (this != &other)
    {
        mpq_set(val, other.val);
        
    }
    return *this;
}

void Ordinary::print() const
{

    gmp_printf("%Zd\n", val);
}

void Ordinary::printWithInfo() const
{

    gmp_printf("%Zd\n", val);

}

double Ordinary::toDecimal() const
{
    return mpq_get_d(val);
}

Ordinary Ordinary::operator+(const Ordinary &other) const
{
    Ordinary res; // создается 0/1
    mpq_add(res.val, this->val, other.val);
    mpq_canonicalize(res.val);
    return res;
}
string Ordinary::toString() const
{

    char *c_num = mpq_get_str(NULL, 10, val);
    string res(c_num);
    free(c_num);
    return res;
}
Ordinary Ordinary::operator-(const Ordinary &other) const
{
    Ordinary res; // создается 0/1
    mpq_sub(res.val, this->val, other.val);
    mpq_canonicalize(res.val);
    return res;
}

Ordinary Ordinary::operator*(const Ordinary &other) const
{

    Ordinary res;
    mpq_mul(res.val, this->val, other.val);
    mpq_canonicalize(res.val);
    return res;
}

Ordinary Ordinary::operator/(const Ordinary &other) const
{

    if (mpq_sgn(other.val) == 0)
    {
        cout << "Ошибка! Деление на ноль!" << endl;
        exit(1);
    }
    Ordinary res; // создается 0/1
    mpq_div(res.val, this->val, other.val);
    mpq_canonicalize(res.val);
    return res;
}
