#ifndef FRACTION_H
#define FRACTION_H
#include <string>
using namespace std;

bool isNum(string temp);
int gcd(int a, int b);

class Fraction
{
	int numerator;
	int denominator;
public:
	Fraction() { numerator = 0; denominator = 1; }
	Fraction(int numerator, int denominator);
	Fraction operator+(const Fraction &num)const;
	Fraction operator-(const Fraction &num)const;
	Fraction operator-(const int &num)const;
	Fraction operator*(const Fraction &num)const;
	Fraction operator/(const Fraction &num)const;
	bool operator==(const Fraction &num)const;
	bool operator==(const int &num)const;
	bool operator<(const int &num)const;
	bool operator>(const int &num)const;
	Fraction &operator=(const string &fra);
	Fraction &operator=(const int &ntgr);
	Fraction operator+=(const Fraction &num);
	Fraction operator-=(const Fraction &num);
	Fraction operator-=(const int &num);
	Fraction operator--();
	Fraction operator--(int);
	Fraction operator*=(const Fraction &num);
	Fraction operator/=(const Fraction &num);
	string toString()const;
	string toStr()const;
	bool isInteger()const;
	friend ostream &operator<<(ostream &output, const Fraction &num);
};

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
		if (!positive)//not zero is true
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

inline bool Fraction::operator<(const int &num)const
{
	return numerator < num*denominator;
}

inline bool Fraction::operator>(const int & num) const
{
	return numerator > num*denominator;
}

Fraction &Fraction::operator=(const string &fra)
{
	size_t index;
	string fraction = fra;
	if (fraction == "")//special values
		numerator = denominator = 1;
	else if (fraction == "-")
	{//special values
		numerator = -1;
		denominator = 1;
	}
	else
	{
		if (!isNum(fraction))
			throw "Not number!";
		//count the negative sign, double negative is positive
		int negative = count(fraction.begin(), fraction.end() - 1, '-');

		if ((index = fraction.find('(', 0)) != string::npos)
		{//erase the brackets
			if (index == 1)
				fraction.erase(0, 1);//there should be a negative sign, erase it, because once the numerator starts with a negative sign, string --a cannot turn to integer
			fraction.erase(0, 1);
			fraction.erase(fraction.find(')', 1), 1);
		}

		//break down the string and get the munerator and dnominator
		index = fraction.find('/', 0);
		if (index != string::npos)
		{
			numerator = abs(atoi(fraction.substr(0, index).c_str()));
			denominator = abs(atoi(fraction.substr(index + 1).c_str()));
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
		if (negative % 2 == 1)
			numerator = -numerator;
	}
	return *this;
}

inline Fraction &Fraction::operator=(const int &ntgr)
{
	this->numerator = ntgr;
	this->denominator = 1;
	return *this;
}

inline Fraction Fraction::operator+=(const Fraction &num)
{
	*this = *this + num;
	return *this;
}

inline Fraction Fraction::operator-=(const Fraction &num)
{
	*this = *this - num;
	return *this;
}

inline Fraction Fraction::operator-=(const int &num)
{
	*this = *this - num;
	return *this;
}

inline Fraction Fraction::operator--()
{
	*this = *this - 1;
	return *this;
}

inline Fraction Fraction::operator--(int)
{
	Fraction old = *this;
	*this = *this - 1;
	return old;
}

inline Fraction Fraction::operator*=(const Fraction & num)
{
	*this = *this * num;
	return *this;
}

inline Fraction Fraction::operator/=(const Fraction & num)
{
	*this = *this / num;
	return *this;
}

inline string Fraction::toString()const
{
	if (*this == 1)
		return "";
	else if (*this == -1)
		return "-";
	else if (denominator == 1)
		return to_string(numerator);
	else
		return "(" + to_string(numerator) + "/" + to_string(denominator) + ")";
}

inline string Fraction::toStr()const
{
	if (*this == 1)
		return "";
	else if (*this == -1)
		return "-";
	else if (denominator == 1)
		return to_string(numerator);
	else
		return to_string(numerator) + "/" + to_string(denominator);
}

inline bool Fraction::isInteger()const
{
	return denominator == 1;
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