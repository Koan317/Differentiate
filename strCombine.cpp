#ifndef STRCOMBINE_H
#define STRCOMBINE_H
#include <cstdarg>
#include <string>
using namespace std;

char *strCombine(char *str, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, str);
	char *temp = va_arg(arg_ptr, char*);
	do {
		strcat(str, temp);
	} while ((temp = va_arg(arg_ptr, char*)) != NULL && temp != "");
	va_end(arg_ptr);
	return str;
}
#endif