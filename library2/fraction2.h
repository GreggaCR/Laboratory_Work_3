#ifndef FRACTION2_H
#define FRACTION2_H

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
    mpq_t val;
    
};


#endif
