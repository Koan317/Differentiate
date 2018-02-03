#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include "Fraction.h"
using namespace std;

bool differentiate(char polynomial[], char result[]);
string fractionMultiplication(string num1, string num2);
string fractionDivision(string num1, string num2);
string fractionAddition(string num1, string num2);
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
		for (int i = 0; result[i] != '\0'; ++i)
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
		result = "-1";
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
		Fraction multiple(temp);
		if (multiple == 0)
		{
			result[0] = '0';
			return true;
		}
		else

		return true;
	}
	/********f(x)=ax end********/
	/********f(x)=ax^n********/
	if ((index = monomial.find("x^", 0)) != string::npos)
	{//atoi() cannot throw any exception automatically, so we cannot use try/catch
		string multiple = monomial.substr(0, index);
		string exponent = monomial.substr(index + 2);

		if (index == 0)//such as x^2
			multiple = "1/1";
		else if (multiple.front() == '-' && index == 1)//such as -x^2
			multiple = "-1/1";
		else if (multiple.find('/', 0) == string::npos)//is another integer
			multiple += "/1";

		if (index == monomial.size() - 2)
		{
			cerr << "Exponent is missed, check out the monomial you input." << endl;
			return false;
		}
		else if (exponent.find('x', 0) != string::npos)
		{
			cerr << "x^x is not supported." << endl;
			return false;
		}
		else if (exponent.find('/', 0) == string::npos)
		{//is integer
			if (atoi(exponent.c_str()) == 0)
			{
				result[0] = '0';
				return true;
			}
			exponent += "/1";
		}

		multiple = fractionMultiplication(multiple, exponent);
		exponent = fractionAddition(exponent, "-1/1");
		if (multiple == "error" || exponent == "error")
			return false;
		else if (multiple == "0")
		{
			result[0] = '0';
			return true;
		}

		//pack the multiple
		if (multiple == "1")
			multiple = "";
		//when pack the exponent, if exponent equals one
		if (exponent == "1")
			temp = multiple + "x";
		else//if exponent is another number(no matter integer or fraction)
			temp = multiple + "x^" + exponent;

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
		string multiple, base, tempstr;
		bool negativebase = false;
		index = temp.find('e', 0);
		if (isNum(temp))//such as 2^x
		{
			base = fractionMultiplication(temp, "1/1");
			multiple = "";
		}
		else if (index != string::npos && (isNum(tempstr = temp.substr(0, index)) || tempstr.empty() || tempstr == "-"))//such as 2e^x
		{
			base = "e";
			if (tempstr.empty())
				tempstr = "1/1";
			else if (tempstr == "-")
				tempstr = "-1/1";
			multiple = fractionMultiplication(tempstr, "1/1");
		}
		else if (temp.front() == '(')//such as (1/2)3^x
		{
			index = temp.find(')', 1);
			if ((index + 1) != monomial.find("^x", 0))
			{//(1/2)3^x
				multiple = fractionMultiplication(temp.substr(0, index + 1), "1/1");
				base = fractionMultiplication(temp.substr(index + 1), "1/1");
			}
			else
			{//(1/2)^x
				multiple = "";
				base = fractionMultiplication(temp.substr(0, index + 1), "1/1");
			}
		}
		else if (temp.back() == ')')//such as 2(1/3)^x or (1/2)(3/4)^x
		{
			index = temp.find('(', 0);
			multiple = fractionMultiplication(temp.substr(0, index), "1/1");
			base = fractionMultiplication(temp.substr(index + 1), "1/1");
		}

		if (multiple == "1")
			multiple = "";
		else if (multiple == "-1")
			multiple = "-";
		if (base == "1")
		{
			result[0] = '0';
			return true;
		}
		if (base == "e" && multiple != "1")
			temp = multiple + base + "^x";
		else if (base == "e" && multiple == "1")
			temp = base + "^x";
		else
			temp = multiple + "ln" + base + "¡¤" + base + "^x";
		strcpy_s(result, temp.size() + 1, temp.c_str());
		return true;
	}
	/********f(x)=an^x end********/
	/********f(x)=nlog!ax********/
	if ((index = monomial.find("ln", 0)) != string::npos)
	{
		string multiple = monomial.substr(0, index);
		string base = monomial.substr(index + 2);
		index = base.find('x', 0);
		base.erase(index, 1);
		if (multiple == "")
			multiple = "1/1";
		if (base == "")
			base = "1/1";

		if (isNum(multiple) && isNum(base))
			multiple = fractionMultiplication(multiple, "1/1");
		else
		{
			cerr << "Illegal characters in monomial!" << endl;
			return false;
		}
		if (multiple.find('/', 0) != string::npos)
		{
			temp = multiple.insert(multiple.find(')', 0) - 1, 1, 'x');
			temp.erase(temp.find('(', 0), 1);
			temp.erase(temp.find(')', 1), 1);
		}
		else
			temp = multiple + "/x";
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