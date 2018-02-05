#include <iostream>
using namespace std;

bool differentiate(char polynomial[], char result[]);

int main()
{
	char polynomial[200] = { '\0' };
	char result[200] = { '\0' };
	while (1)
	{
		cout << "Input the monomial you want to defferentiate. Only unknow number x is legal." << endl;
		cout << "Tips: superscript: ^\tsubscript: !\tmultiplication sign: omitted\tdivision sign: /\tupgrade the priority: ()" << endl;
		cout << "When the base is less than zero in exponential function, result will be out of real number range." << endl;
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