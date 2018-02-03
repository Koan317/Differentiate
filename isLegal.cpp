#ifndef ISLGL_H
#define ISLGL_H
#include <iostream>
#include <string>
using namespace std;

bool isNum(string temp);

bool isLegal(string temp)
{
	string::iterator it;
	//remove the operators of temp
	for (it = temp.begin(); it != temp.end();)//in this loop, brackets will not be erase, they will be removed in the function isNum
		if (*it == 'x')
			temp.erase(it);
		else if (*it == '+')
			temp.erase(it);
		else if (*it == '-')
			temp.erase(it);
		else if (*it == '/')
			temp.erase(it);
		else if (*it == 's')
		{//remove sin
			if (it + 1 == temp.end() || it + 2 == temp.end())
			{//do not merge with the last branch(else branch), it + 1 may be out of range and then *(it + 1) will throw the exception
				cerr << "The monomial includes illegal characters(bad sin)." << endl;
				return false;
			}
			else if (*(it + 1) == 'i'&&*(it + 2) == 'n')
			{
				temp.erase(it);
				temp.erase(it);
				temp.erase(it);
			}
			else
			{
				cerr << "The monomial includes illegal characters(bad sin)." << endl;
				return false;
			}
		}
		else if (*it == 'c')
		{//remove cos
			if (it + 1 == temp.end() || it + 2 == temp.end())
			{//do not merge with the last branch(else branch), it + 1 may be out of range and then *(it + 1) will throw the exception
				cerr << "The monomial includes illegal characters(bad cos)." << endl;
				return false;
			}
			else if (*(it + 1) == 'o'&&*(it + 2) == 's')
			{
				temp.erase(it);
				temp.erase(it);
				temp.erase(it);
			}
			else
			{
				cerr << "The monomial includes illegal characters(bad cos)." << endl;
				return false;
			}
		}
		else if (*it == 't')
		{//remove tan
			if (it + 1 == temp.end() || it + 2 == temp.end())
			{//do not merge with the last branch(else branch), it + 1 may be out of range and then *(it + 1) will throw the exception
				cerr << "The monomial includes illegal characters(bad tan)." << endl;
				return false;
			}
			else if (*(it + 1) == 'a'&&*(it + 2) == 'n')
			{
				temp.erase(it);
				temp.erase(it);
				temp.erase(it);
			}
			else
			{
				cerr << "The monomial includes illegal characters(bad tan)." << endl;
				return false;
			}
		}
		else if (*it == '^')
			temp.erase(it);
		else if (*it == '!')
			temp.erase(it);
		else if (*it == 'l')
		{//remove log, ln, lg
			if (it + 1 == temp.end())
			{//do not merge with the last branch(else branch), it + 1 may be out of range and then *(it + 1) will throw the exception
				cerr << "The monomial includes illegal characters(bad log/ln/lg)." << endl;
				return false;
			}
			else if (*(it + 1) == 'n' || *(it + 1) == 'g')
			{//ln and lg
				temp.erase(it);
				temp.erase(it);
			}
			else if (it + 2 == temp.end())
			{
				cerr << "The monomial includes illegal characters(bad ln/lg)." << endl;
				return false;
			}
			else if (*(it + 1) == 'o'&&*(it + 2) == 'g')
			{//log
				temp.erase(it);
				temp.erase(it);
				temp.erase(it);
			}
			else
			{
				cerr << "The monomial includes illegal characters(bad log)." << endl;
				return false;
			}
		}
		else if (*it == 'e')
			temp.erase(it);
		else
			++it;

	//then judge whether the rest of string includes illegal characters
	if (!isNum(temp) && !temp.empty())
	{
		cerr << "The monomial includes illegal characters(not number)." << endl;
		return false;
	}
	//now the initial string is legal
	return true;
}
#endif // !ISLGL_H