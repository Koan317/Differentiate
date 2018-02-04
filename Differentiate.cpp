#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include "Fraction.h"
using namespace std;

bool differentiate(char polynomial[], char result[]);
bool isNum(string temp);
bool isLegal(string temp);

int main()
{
	char polynomial[200] = { '\0' };
	char result[200] = { '\0' };
	while (1)
	{
		cout << "Input the monomial you want to defferentiate. Only unknow number x is legal." << endl;
		cout << "Tips: superscript: ^\tsubscript: !\tmultiplication sign: omitted\tdivision sign: /\tupgrade the priority: ()" << endl;
		cout << "f(x)=";
		cin >> polynomial;
		int stat = differentiate(polynomial, result);
		if (stat)
			cout << "Result is f'(x)=" << result << endl;
		for (int i = 0; result[i] != '\0'; i++)
			result[i] = '\0';
		cout << "Press any key to continue..." << endl;
		getchar();
		getchar();
		system("cls");
	}
	return 0;
}

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
	if ((index = monomial.find("x^", 0)) != string::npos)
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
		temp = multiple.toString() + "x^" + exponent.toString();
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return result;
	}
	/********f(x)=ax^n end********/
	/********f(x)=an^x********/
	if ((index = monomial.find("^x", 0)) != string::npos)
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
			if (index == 0 || isNum(temp = temp.substr(0, index)))
			{//ae^x
				try {
					multiple = temp;
				}
				catch (const char* msg)
				{
					cerr << msg << endl;
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
		temp = multiple.toString() + "ln" + base.toString() + "¡¤" + base.toString() + "^x";
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	/********f(x)=an^x end********/
	/********f(x)=nlog!ax********/
	if ((index = monomial.find("ln", 0)) != string::npos)
	{
		if (index + 2 >= monomial.size())
		{
			cerr << "Real number missed, check out the monimial you input." << endl;
			return false;
		}
		temp = monomial.substr(0, monomial.size() - 1);//remove variable x
		Fraction multiple, base;
		try {
			multiple = monomial.substr(0, index);
			base = monomial.substr(index + 2);
		}
		catch (const char *msg)
		{
			cerr << msg << endl;
			return false;
		}

		if (multiple.isInteger())
			temp = multiple.toString() + "/x";
		else
			temp = multiple.toString().insert(multiple.toString().find(')', 1) - 1, 1, 'x');
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	if ((index = monomial.find("lg", 0)) != string::npos)
	{

	}
	/********f(x)=nlog!ax end********/
	/********f(x)=sinx********/
	/********f(x)=sinx end********/
	/********f(x)=cosx********/
	/********f(x)=cosx end********/
	/********f(x)=tanx********/
	/********f(x)=tanx end********/
}