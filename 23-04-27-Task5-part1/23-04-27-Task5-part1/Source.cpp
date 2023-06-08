#include <iostream>
#include <clocale>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


double ro(double x)
{
	return 1;
}


double f(double x)
{
	return pow(M_E, 2 * x);
}



int main()
{
	setlocale(LC_ALL, "Russian");

	cout << setprecision(15);

	return EXIT_SUCCESS;
}