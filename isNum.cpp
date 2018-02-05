#ifndef ISNUM_H
#define ISNUM_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool isNum(string temp)
{//negative numbers also can be recognized correctly
	if (temp.size() > 0 && temp.front() == '-')
		temp.erase(0, 1);//if there is a negative sign, erase it, because once the numerator starts with a negative sign, string --a cannot turn to integer
	size_t index_a = temp.find('(', 0);//use for judge fractions
	size_t index_b = temp.find(')', 1);//find from 1st item

	if (index_a > index_b || (index_a != string::npos && index_b == string::npos))
	{//only have ( or only have )
		cerr << "Brackets are not match, check out the monomial you input." << endl;
		return false;
	}
	else if ((index_a != string::npos && index_a != 0) || (index_b != string::npos && index_b != temp.size() - 1))//then ( must be the first character and the number is suppossed to end up with )
		return false;//if not, it is an integer connects with a fraction or something strange

	if (index_a != string::npos)//remove the brackets
	{//if ( exists, ) must exist too
		temp.erase(index_a, 1);
		temp.erase(index_b - 1, 1);//after ( removed, the index of ) is suppossed to move forward
	}

	index_a = temp.find('/', 0);//reuse variable, avoid to declare too many parameters
	if (index_a == 0 || (index_a == temp.size() - 1 && index_a != string::npos))
	{
		cerr << "The fraction misses numerator or denominator." << endl;
		return false;
	}

	string numerator, denominator;
	if (index_a != string::npos)
	{
		numerator = temp.substr(0, index_a);
		denominator = temp.substr(index_a + 1);
	}
	else
	{
		numerator = temp;
		denominator = "1";
	}

	stringstream strin1(numerator);
	stringstream strin2(denominator);
	double d;
	char c;
	if (!(strin1 >> d))//if current string starts with a character, this branch will be executed
		return false;
	if (strin1 >> c)//if current string starts with a number but contains characters, this branch will be executed
		return false;
	if (!(strin2 >> d))
		return false;
	if (strin2 >> c)
		return false;

	return true;
}
#endif // !ISNUM_H
