#include "fraction.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <gmpxx.h>
using namespace std;


Ordinary::Ordinary()
{

    mpz_init(num);
    mpz_init(den);

    mpz_set_si(num, 0);
    mpz_set_si(den, 1);

    wasReduced = false;
   
}

void Ordinary::input()
{	long long n, d;

    cout << "Введите числитель и знаменатель через пробел: ";
    cin >> n >> d;

    if (d == 0)
    {
        cout << "Ошибка! Деление на ноль!" << endl;
        exit(1);
    }

    mpz_set_si(num, n);
    mpz_set_si(den, d);

    wasReduced = false;
    reduce();
	
	}

Ordinary::Ordinary(long long n, long long d) {
    if (d == 0) d = 1; // Защита от деления на 0
    mpz_init_set_si(num, n);
    mpz_init_set_si(den, d);
 
    wasReduced = false;
    reduce();
}

Ordinary::Ordinary(const Ordinary &other)
{

    mpz_init(num);
    mpz_init(den);

    mpz_set(num, other.num);
    mpz_set(den, other.den);

    wasReduced = other.wasReduced;
}

Ordinary::~Ordinary()
{
    mpz_clear(num);
    mpz_clear(den);
}

Ordinary Ordinary::operator=(const Ordinary &other){
	if(this != &other){
		mpz_set(num,other.num);
		mpz_set(den,other.den);
		wasReduced = other.wasReduced;
		}
		return *this;
	
	}

void Ordinary::reduce() {
    mpz_t g;
    mpz_init(g);
    mpz_gcd(g, num, den);
    mpz_divexact(num, num, g);
    mpz_divexact(den, den, g);
    if (mpz_sgn(den) < 0) {
        mpz_neg(num, num);
        mpz_neg(den, den);
    }
    mpz_clear(g);
}


void Ordinary::print() const
{

    gmp_printf("%Zd/%Zd\n", num, den);
}

void Ordinary::printWithInfo() const
{

    gmp_printf("%Zd/%Zd", num, den);

    if (wasReduced)
        cout << "  (дробь была сокращена)";

    cout << endl;
}

double Ordinary::toDecimal() const
{

    double n = mpz_get_d(num);
    double d = mpz_get_d(den);

    return n / d;
}

Ordinary Ordinary::operator+(const Ordinary &other) const {
    Ordinary res; // создается 0/1
    mpz_t t1, t2;
    mpz_init(t1); mpz_init(t2);

    mpz_mul(t1, num, other.den);
    mpz_mul(t2, other.num, den);
    mpz_add(res.num, t1, t2);
    mpz_mul(res.den, den, other.den);

    mpz_clear(t1); mpz_clear(t2);
    res.reduce();
    return res;
}
string Ordinary::toString() const {

    char* c_num = mpz_get_str(NULL, 10, num);
    string res(c_num);
    free(c_num); 

    if (mpz_cmp_ui(den, 1) != 0) {
        char* c_den = mpz_get_str(NULL, 10, den);
        res += "/";
        res += c_den;
        free(c_den);
    }
    return res;
}
Ordinary Ordinary::operator-(const Ordinary &other) const {
    Ordinary res; // создается 0/1
    mpz_t t1, t2;
    mpz_init(t1); mpz_init(t2);

    mpz_mul(t1, num, other.den);
    mpz_mul(t2, other.num, den);
    mpz_sub(res.num, t1, t2);
    mpz_mul(res.den, den, other.den);

    mpz_clear(t1); mpz_clear(t2);
    res.reduce();
    return res;
}

Ordinary Ordinary::operator*(const Ordinary &other) const
{

    Ordinary result(0, 1);

    mpz_mul(result.num, num, other.num);
    mpz_mul(result.den, den, other.den);

    result.reduce();
    return result;
}

Ordinary Ordinary::operator/(const Ordinary &other) const
{

    if (mpz_cmp_ui(other.num, 0) == 0)
    {
        cout << "Ошибка! Деление на ноль!" << endl;
        exit(1);
    }

    Ordinary result(0, 1);

    mpz_mul(result.num, num, other.den);
    mpz_mul(result.den, den, other.num);

    result.reduce();
    return result;
}
