#ifndef FRACTION_H
#define FRACTION_H

#include <string>
#include <gmp.h>
class Ordinary
{
public:
    Ordinary();
    Ordinary(long long n, long long d);
    Ordinary(const Ordinary &other);
    Ordinary operator=(const Ordinary &other);
    ~Ordinary();
	void input();
    void print() const;
    void printWithInfo() const;
    double toDecimal() const;

	std::string toString() const;

    Ordinary operator+(const Ordinary &other) const;
    Ordinary operator-(const Ordinary &other) const;
    Ordinary operator*(const Ordinary &other) const;
    Ordinary operator/(const Ordinary &other) const;

private:
    mpz_t num;
    mpz_t den;
    bool wasReduced;
	
    void reduce();
    
};


#endif
