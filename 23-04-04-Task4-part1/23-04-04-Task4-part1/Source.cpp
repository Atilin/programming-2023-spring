#include <iostream>
#include <clocale>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


double f(double x)
{
	return sin(x) - x / 2;
}
double f_i(double x)
{
	return -x * x / 4 - cos(x);
}

double f0(double x)
{
	return 5;
}
double f0_i(double x)
{
	return 5 * x;
}

double f1(double x)
{
	return x - 2;
}
double f1_i(double x)
{
	return -2 * x + x * x / 2;
}

double f2(double x)
{
	return x * x + 4 * x + 3;
}
double f2_i(double x)
{
	return 3 * x + 2 * x * x + x * x * x / 3;
}

double f3(double x)
{
	return x * x * x + 7 * x * x + 4 * x - 1;
}
double f3_i(double x)
{
	return -x + 2 * x * x + (7 * x * x * x) / 3 + x * x * x * x / 4;
}



int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Приближённое вычисление интеграла по квадратурным формулам" << endl << endl;


	cout << "f(x) = sin(x) - x / 2" << endl << endl;
	cout << "Введите границы интегрирования:" << endl;
	cout << "Левая граница: ";
	double a;
	cin >> a;
	cout << "Правая граница: ";
	double b;
	cin >> b;

	double exact_value = f_i(b) - f_i(a);
	cout << endl << "Точное значение интеграла функции f(x): " << exact_value << endl;

	double left = f(a) * (b - a);
	cout << "КФ левого прямоугольника: " << left << endl;

	double right = f(b) * (b - a);
	cout << "КФ правого прямоугольника: " << right << endl;

	double mid = f((b + a) / 2) * (b - a);
	cout << "КФ среднего прямоугольника: " << mid << endl;

	double trapeze = (f(a) + f(b)) * (b - a) / 2;
	cout << "КФ трапеции: " << trapeze << endl;

	double simpson = (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6;
	cout << "КФ Симпсона: " << simpson << endl;

	double h = (b - a) / 3;
	double three_eight = (f(a) / 8 + f(a + h) * 3 / 8 + f(a + 2 * h) * 3 / 8 + f(b) / 8) * (b - a);
	cout << "КФ 3/8: " << three_eight << endl << endl;



	cout << "Абсолютная фактическая погрешность КФ левого прямоугольника: " << abs(left - exact_value) << endl;

	cout << "Абсолютная фактическая погрешность КФ правого прямоугольника: " << abs(right - exact_value) << endl;

	cout << "Абсолютная фактическая погрешность КФ среднего прямоугольника: " << abs(mid - exact_value) << endl;

	cout << "Абсолютная фактическая погрешность КФ трапеции: " << abs(trapeze - exact_value) << endl;

	cout << "Абсолютная фактическая погрешность КФ Симпсона: " << abs(simpson - exact_value) << endl;

	cout << "Абсолютная фактическая погрешность КФ 3/8: " << abs(three_eight - exact_value) << endl << endl;

	cout << "------------------------------------------------------------------" << endl << endl;



	cout << "ПРОВЕРКА:" << endl << endl;

	cout << "f(x) = 5" << endl;
	double exact_value0 = f0_i(b) - f0_i(a);

	double left0 = f0(a) * (b - a);
	cout << "КФ левого прямоугольника: " << left0 << endl;
	cout << "Абсолютная фактическая погрешность КФ левого прямоугольника: " << abs(left0 - exact_value0) << endl;

	double right0 = f0(b) * (b - a);
	cout << "КФ правого прямоугольника: " << right0 << endl;
	cout << "Абсолютная фактическая погрешность КФ правого прямоугольника: " << abs(right0 - exact_value0) << endl;

	double mid0 = f0((b + a) / 2) * (b - a);
	cout << "КФ среднего прямоугольника: " << mid0 << endl;
	cout << "Абсолютная фактическая погрешность КФ среднего прямоугольника: " << abs(mid0 - exact_value0) << endl << endl;


	cout << "f(x) = x-2" << endl;
	double exact_value1 = f1_i(b) - f1_i(a);

	double trapeze1 = (f1(a) + f1(b)) * (b - a) / 2;
	cout << "КФ трапеции: " << trapeze1 << endl;
	cout << "Абсолютная фактическая погрешность КФ трапеции: " << abs(trapeze1 - exact_value1) << endl << endl;


	cout << "f(x) = x ^ 2 + 4 * x + 3" << endl;
	double exact_value2 = f2_i(b) - f2_i(a);

	double simpson2 = (f2(a) + 4 * f2((a + b) / 2) + f2(b)) * (b - a) / 6;
	cout << "КФ Симпсона: " << simpson2 << endl;
	cout << "Абсолютная фактическая погрешность КФ Симпсона: " << abs(simpson2 - exact_value2) << endl << endl;


	cout << "f(x) = x ^ 3 + 7 * x ^ 2 + 4 * x - 1" << endl;
	double exact_value3 = f3_i(b) - f3_i(a);
	cout << exact_value3 << endl;

	double h3 = (b - a) / 3;
	double three_eight3 = (b - a) * (f3(a) / 8 + f3(a + h3) * 3 / 8 + f3(a + 2 * h3) * 3 / 8 + f3(b) / 8);
	cout << "КФ 3/8: " << three_eight3 << endl;
	cout << "Абсолютная фактическая погрешность КФ 3/8: " << abs(three_eight3 - exact_value3) << endl << endl;


	return EXIT_SUCCESS;
}