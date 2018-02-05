#include <iostream>
#include <string>
#include "Fraction.h"
using namespace std;

bool differentiate(char polynomial[], char result[]);
bool isNum(string temp);
bool isLegal(string temp);

bool differentiate(char polynomial[], char result[])
{
	string::iterator it;//use for going through the string to format it
	string temp = polynomial;//use for checking whether string contains illegal characters and being temporary variable
	string monomial = temp;//use for calculating
	size_t index = 0;

	/********special values********/
	if (temp == "x")
	{//special value: (x)'=1
		result[0] = '1';
		return true;
	}
	else if (temp == "-x")
	{//special value: (-x)'=-1
		strcpy_s(result, 3, "-1");
		return true;
	}
	/********special values end********/

	if (!isLegal(temp))//judge after the special value
		return false;

	/********f(x)=C********/
	if (monomial.find('x', 0) == string::npos)
	{
		result[0] = '0';
		return true;
	}
	/********f(x)=C end********/
	/********f(x)=ax********/
	else if (monomial.back() == 'x' && isNum(temp = monomial.substr(0, monomial.size() - 1)))
	{//(ax)'=a
		Fraction multiple;
		try {
			multiple = temp;
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}
		if (multiple == 0)
			result[0] = '0';
		else
		{
			temp = multiple.toString();
			strcpy_s(result, temp.size() + 1, temp.c_str());
		}
		return true;
	}
	/********f(x)=ax end********/
	/********f(x)=ax^n********/
	else if ((index = monomial.find("x^", 0)) != string::npos)
	{
		if (index == monomial.size() - 2)
		{
			cerr << "Exponent is missed, check out the monomial you input." << endl;
			return false;
		}
		Fraction multiple, exponent;
		try {
			multiple = monomial.substr(0, index);
			exponent = monomial.substr(index + 2);
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}

		if (multiple == 0 || exponent == 0)
		{
			result[0] = '0';
			return true;
		}

		multiple *= exponent;
		exponent--;
		if (exponent == 1)
			temp = multiple.toString() + "x";
		else
			temp = multiple.toString() + "x^" + exponent.toString();
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return result;
	}
	/********f(x)=ax^n end********/
	/********f(x)=an^x********/
	else if ((index = monomial.find("^x", 0)) != string::npos)
	{
		if (index == 0)
		{
			cerr << "Base is missed, check out the monimial you input." << endl;
			return false;
		}
		else if (index + 2 != monomial.size())
		{
			cerr << "Too many characters after variable x." << endl;
			return false;
		}
		temp = monomial.substr(0, index);
		Fraction multiple, base;
		index = temp.find('e', 0);
		if (index != string::npos)
			if (index == 0 || temp.front() == '-' || isNum(temp.substr(0, index)))
			{//ae^x
				temp = temp.substr(0, index);
				try {
					multiple = temp;
				}
				catch (const char* msg)
				{
					cerr << msg << endl;
					return false;
				}
				temp = multiple.toString() + "e^x";
				strcpy_s(result, temp.size() + 1, temp.c_str());
				return true;
			}
			else
			{
				cerr << "Bad multiple in ae^x, check out the monimial you input." << endl;
				return false;
			}
		else
		{
			if (isNum(temp))
			{//2^x, -2^x, (-2)^x, (1/2)^x, (-1/2)^x, -(1/2)^x...
				if (temp.front() == '-')
				{
					try {
						base = temp.substr(1);
						multiple = -1;
					}
					catch (const char *msg)
					{
						cerr << msg << endl;
						return false;
					}
				}
				else
				{
					try {
						base = temp;
						multiple = 1;
					}
					catch (const char *msg)
					{
						cerr << msg << endl;
						return false;
					}
				}
			}
			else if (temp.front() == '(')
			{//(-2)2^x, (1/2)2^x, (-1/2)(-2)^x, (1/2)(-1/2)^x, (-1/2)(1/2)^x...
				index = temp.find(')', 1);
				try {
					multiple = temp.substr(0, index);
					base = temp.substr(index);
				}
				catch (const char *msg)
				{
					cerr << msg << endl;
					return false;
				}
			}
			else
			{//2(1/2)^x, -2(-1/2)^x...
				index = temp.find('(', 1);
				try {
					multiple = temp.substr(0, index);
					base = temp.substr(index);
				}
				catch (const char *msg)
				{
					cerr << msg << endl;
					return false;
				}
			}
		}

		if (base == 1)
		{
			result[0] = '0';
			return true;
		}
		if (base < 0 && base.isInteger())
			temp = multiple.toString() + "ln(" + base.toString() + ")，(" + base.toString() + ")^x";
		else
			temp = multiple.toString() + "ln" + base.toString() + "，" + base.toString() + "^x";
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	/********f(x)=an^x end********/
	/********f(x)=nlog!ax********/
	else if ((index = monomial.find("ln", 0)) != string::npos)
	{
		if (index + 2 >= monomial.size())
		{
			cerr << "Real number missed, check out the monimial you input." << endl;
			return false;
		}
		temp = monomial.substr(0, monomial.size() - 1);//remove variable x
		Fraction multiple, real;
		try {
			multiple = temp.substr(0, index);
			real = temp.substr(index + 2);
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}

		if (multiple.isInteger())
			if (multiple == 1)
				temp = "1/x";//toString omit the multiple when value is 1
			else
				temp = multiple.toString() + "/x";
		else
			temp = multiple.toString().insert(multiple.toString().find(')', 1), 1, 'x');
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	else if ((index = monomial.find("lg", 0)) != string::npos)
	{
		if (index + 2 >= monomial.size())
		{
			cerr << "Real number missed, check out the monimial you input." << endl;
			return false;
		}
		temp = monomial.substr(0, monomial.size() - 1);//remove variable x
		Fraction multiple, real;
		try {
			multiple = temp.substr(0, index);
			real = temp.substr(index + 2);
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}

		if (multiple.isInteger())
			if (multiple == 1)
				temp = "1/(x，ln10)";//toString omit the multiple when value is 1
			else
				temp = multiple.toString() + "/(x，ln10)";
		else
		{
			temp = multiple.toString();
			temp = temp.erase(temp.size() - 1, 1).insert(temp.find('/', 1) + 1, 1, '(') + "x，ln10))";//remove the last ) then splice the rest string
		}
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	else if ((index = monomial.find("log!", 0)) != string::npos)
	{
		if (index + 4 >= monomial.size())
		{
			cerr << "Real number missed, check out the monimial you input." << endl;
			return false;
		}
		temp = monomial.substr(0, monomial.size() - 1);//remove variable x
		Fraction multiple, real, base;
		try {
			multiple = temp.substr(0, index);
			if ((index = (temp = temp.substr(index + 4)).find(')', 0)) == string::npos)
				base = temp;
			else
			{
				base = temp.substr(0, index + 1);
				real = temp.substr(index + 1);
			}
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}

		if (multiple.isInteger())
			if (multiple == 1)
				temp = "1/(x，ln" + base.toString() + ")";//toString omit the multiple when value is 1
			else
				temp = multiple.toString() + "/(x，ln" + base.toString() + ")";
		else
		{
			temp = multiple.toStr();
			temp = temp.insert(temp.find('/', 1) + 1, 1, '(') + "x，ln" + base.toString() + ")";//remove the last ) then splice the rest string
		}
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	/********f(x)=nlog!ax end********/
	/********f(x)=sinx********/
	else if ((index = monomial.find("sin", 0)) != string::npos)
	{
		if (index + 3 >= monomial.size())
		{
			cerr << "Radian missed, check out the monomial you input." << endl;
			return false;
		}
		temp = monomial.substr(0, monomial.size() - 1);
		Fraction multiple1, multiple2;
		try {
			multiple1 = temp.substr(0, index);
			multiple2 = temp.substr(index + 3);
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}

		temp = (multiple1*multiple2).toString() + "cos" + multiple2.toString() + "x";
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	/********f(x)=sinx end********/
	/********f(x)=cosx********/
	else if ((index = monomial.find("cos", 0)) != string::npos)
	{
		if (index + 3 >= monomial.size())
		{
			cerr << "Radian missed, check out the monomial you input." << endl;
			return false;
		}
		temp = monomial.substr(0, monomial.size() - 1);
		Fraction multiple1, multiple2;
		try {
			multiple1 = temp.substr(0, index);
			multiple2 = temp.substr(index + 3);
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}

		temp = (multiple1*multiple2*Fraction(-1,1)).toString() + "sin" + multiple2.toString() + "x";
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	/********f(x)=cosx end********/
	/********f(x)=tanx********/
	else if ((index = monomial.find("tan", 0)) != string::npos)
	{
		if (index + 3 >= monomial.size())
		{
			cerr << "Radian missed, check out the monomial you input." << endl;
			return false;
		}
		temp = monomial.substr(0, monomial.size() - 1);
		Fraction multiple1, multiple2;
		try {
			multiple1 = temp.substr(0, index);
			multiple2 = temp.substr(index + 3);
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}

		Fraction multi = multiple1 * multiple2;
		temp = multi.toStr();
		if (multi.isInteger())
			if (multi == 1)
				temp = "1/(cos" + multiple2.toString() + "x)^2";
			else
				temp = temp + "/(cos" + multiple2.toString() + "x)^2";
		else
			temp = temp.insert(temp.find('/', 1) + 1, 1, '(') + "(cos" + multiple2.toString() + "x)^2)";
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	/********f(x)=tanx end********/
	else
	{
		cerr << "Cannot parse the monomial!" << endl;
		return false;
	}
}