#ifndef GCD_H
#define GCD_H
#include <iostream>
using namespace std;

int gcd(int a, int b)
{
	if (a  < b)
		swap(a, b);
	return b == 0 ? a : gcd(b, a % b);
}
#endif // !GCD_H