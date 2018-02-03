#ifndef FRACTION_H
#define FRACTION_H
#include <string>
#include "isNum.cpp"
#include "gcd.cpp"
#include "strCombine.cpp"
using namespace std;

class Fraction
{
	int numerator;
	int denominator;
public:
	Fraction() { numerator = 0; denominator = 1; }
	Fraction(string fraction);
	Fraction(int numerator, int denominator);
	Fraction operator+(const Fraction &num)const;
	Fraction operator-(const Fraction &num)const;
	Fraction operator-(const int &num)const;
	Fraction operator*(const Fraction &num)const;
	Fraction operator/(const Fraction &num)const;
	bool operator==(const Fraction &num)const;
	bool operator==(const int &num)const;
	char* operator=(const Fraction &num)const;
	friend ostream &operator<<(ostream &output, const Fraction &num);
};

Fraction::Fraction(string fraction)
{
	size_t index;
	//erase the brackets
	if (index = fraction.find('(', 0) != string::npos)
	{
		fraction.erase(index, 1);
		fraction.erase(fraction.find(')', 1), 1);
	}

	//count the negative sign, double negative is positive
	int negative = count(fraction.begin(), fraction.end() - 1, '-');
	bool positive;
	if (negative % 2 == 0)
		positive = true;
	else
		positive = false;

	//break down the string and get the munerator and dnominator
	index = fraction.find('/', 0);
	if (index != string::npos)
	{
		numerator = abs(atoi(fraction.substr(0, index).c_str()));
		denominator = abs(atoi(fraction.substr(index).c_str()));
		if (denominator == 0)//zero divisor
			throw "Denominator is zero!";
	}
	else
	{
		numerator = abs(atoi(fraction.c_str()));
		denominator = 1;
	}

	//reduction of fraction by Euclidean Algorithm
	int g = gcd(numerator, denominator);
	if (g > 1)
	{
		numerator /= g;
		denominator /= g;
	}
	if (!positive)
		numerator = -numerator;
}

Fraction::Fraction(int numerator, int denominator)
{
	if (denominator == 0)
		throw "Denominator is zero!";
	else
	{
		int positive = -1;
		if (numerator < 0)
			positive++;
		if (denominator < 0)
			positive++;
		//if positive is not 0, the fraction is positive, otherwise it's negative

		this->numerator = abs(numerator);
		this->denominator = abs(denominator);
		int g = gcd(this->numerator, this->denominator);
		if (g > 1)
		{
			this->numerator /= g;
			this->denominator /= g;
		}
		if (positive)
			this->numerator = -this->numerator;
	}
}

inline Fraction Fraction::operator+(const Fraction &num)const
{
	return Fraction(numerator*num.denominator + num.numerator*denominator, denominator*num.denominator);
}

inline Fraction Fraction::operator-(const Fraction &num)const
{
	return Fraction(numerator*num.denominator - num.numerator*denominator, denominator*num.denominator);
}

inline Fraction Fraction::operator-(const int &num)const
{
	return Fraction(numerator - num * denominator, denominator);
}

inline Fraction Fraction::operator*(const Fraction &num)const
{
	return Fraction(numerator*num.numerator, denominator*num.denominator);
}

inline Fraction Fraction::operator/(const Fraction &num)const
{
	return Fraction(numerator*num.denominator, denominator*num.numerator);
}

inline bool Fraction::operator==(const Fraction &num)const
{
	return (this->numerator == num.numerator && this->denominator == num.denominator);
}

inline bool Fraction::operator==(const int &num)const
{
	return (this->denominator == 1 && this->numerator == num);
}

char* Fraction::operator=(const Fraction &num)const
{
	char *temp = NULL;
	if (num.denominator == 1)
		itoa(num.numerator, temp, 10);
	else
		temp = strCombine("(", num.numerator, "/", num.denominator, ")");
	return temp;
}

ostream &operator<<(ostream &output, const Fraction &num)
{
	if (num.denominator == 1)
		output << num.numerator;
	else
		output << '(' << num.numerator << '/' << num.denominator << ')';
	return output;
}
#endif // !FRACTION_H

