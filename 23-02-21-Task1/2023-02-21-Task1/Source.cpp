#include <iostream>
#include <locale.h>
#include <cmath>
#include <vector>
#include <chrono>

using namespace std;

double f(double x)
{
	return 4 * cos(x) + 0.3 * x;
}

void separation(double A, double B, double N, vector <pair <double, double>>& a)
{
	a.erase(a.begin(), a.end());
	double h = (B - A) / N;
	double counter = 0;
	double x1 = A;
	double x2 = x1 + h;
	double y1 = f(x1);
	double y2 = 0;

	while (x2 <= B)
	{
		y2 = f(x2);

		if (y1 * y2 <= 0)
		{
			counter++;
			cout << "В отрезке [" << x1 << ", " << x2 << "] как минимум один корень" << endl;

			pair <double, double> p;
			p.first = x1;
			p.second = x2;
			a.push_back(p);
		}

		x1 = x2;
		x2 = x1 + h;
		y1 = y2;
	}
	cout << "Число корней: " << counter << endl;
}

void bisection(double a, double b, double e)
{
	cout << "МЕТОД БИСЕКЦИИ:" << endl;
	cout << "Начальное приближение к корню: " << (a + b) / 2 << endl;
	int k = 0;
	while ((b - a) > 2 * e)
	{
		double c = (a + b) / 2;

		if (f(a) * f(c) <= 0)
		{
			b = c;
		}
		else
		{
			a = c;
		}
		k++;
	}
	cout << "Конечное приближение к корню: " << (a + b) / 2 << endl;
	cout << "Точность: " << (b - a) / 2 << endl;
	cout << "Количество шагов: " << k << endl;
	cout << "Абсолютная величина невязки: " << abs(f((a + b) / 2)) << endl;
}

double f1(double x) // производная
{
	return 0.3 - 4 * sin(x);
}

void newton(double a, double b, double e)
{
	cout << "МЕТОД НЬЮТОНА:" << endl;

	double c = (a + b) / 2; // первое приближение
	cout << "Начальное приближение к корню: " << c << endl;

	double d = c - f(c) / f1(c); // второе приближение

	int k = 2;
	while (abs(d - c) > e)
	{
		c = d;
		d = c - f(c) / f1(c);

		k++;
	}
	cout << "Конечное приближение к корню: " << d << endl;
	cout << "Точность: " << abs(d - c) << endl;
	cout << "Количество шагов: " << k << endl;
	cout << "Абсолютная величина невязки: " << abs(f(d)) << endl;
}

void newtonMod(double a, double b, double e)
{
	cout << "МЕТОД НЬЮТОНА МОДИФИЦИРОВАННЫЙ:" << endl;

	double c = (a + b) / 2; // первое приближение
	double x0 = c;
	cout << "Начальное приближение к корню: " << c << endl;

	double d = c - f(c) / f1(c); // второе приближение

	int k = 2;
	while (abs(d - c) > e)
	{
		c = d;
		d = c - f(c) / f1(x0);

		k++;
	}
	cout << "Конечное приближение к корню: " << d << endl;
	cout << "Точность: " << abs(d - c) << endl;
	cout << "Количество шагов: " << k << endl;
	cout << "Абсолютная величина невязки: " << abs(f(d)) << endl;
}

void secant(double a, double b, double e)
{
	cout << "МЕТОД СЕКУЩИХ:" << endl;

	double c = b - (f(b) / (f(b) - f(a))) * (b - a);
	cout << "Начальное приближение к корню: " << c << endl;

	int k = 1;


	while (abs(b - c) > e)
	{
		double c_copy = c;
		c = b - (f(b) / (f(b) - f(c_copy))) * (b - c_copy);
		b = c_copy;

		k++;
	}

	cout << "Конечное приближение к корню: " << c << endl;
	cout << "Точность: " << abs(b - c) << endl;
	cout << "Количество шагов: " << k << endl;
	cout << "Абсолютная величина невязки: " << abs(f(c)) << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "ЧИСЛЕННЫЕ МЕТОДЫ РЕШЕНИЯ НЕЛИНЕЙНЫХ УРАВНЕНИЙ (МЕТОД БИСЕКЦИИ)" << endl << endl;

	cout << "Рассматриваем функцию     4 * cos(x) + 0.3 * x" << endl << endl;

	double A = 0;
	cout << "Введите левый конец (A) интервала поиска корней: ";
	cin >> A;
	cout << endl;

	double B = 0;
	cout << "Введите правый конец (B) интервала поиска корней: ";
	cin >> B;
	cout << endl;

	double epsilon = 0;
	cout << "Задайте точность (epsilon): ";
	cin >> epsilon;
	cout << endl;

	//отделение корней

	vector <pair <double, double>> a;
	double N = 0;
	bool flag = 0;
	while (flag == 0)
	{
		cout << "Задайте число N деления на отрезки: " << endl;
		cin >> N;

		separation(A, B, N, a);
		cout << endl;

		cout << "Вас устраивает полученный результат? Если да - введите 1, иначе - 0" << endl;

		cin >> flag;
		cout << endl;
	}

	//уточнение корней, бисекция

	for (int i = 0; i < a.size(); ++i)
	{
		cout << "-------------------------------------" << endl;
		cout << i + 1 << " корень:" << endl << endl;

		auto start = chrono::steady_clock::now();
		bisection(a[i].first, a[i].second, epsilon);
		auto end = chrono::steady_clock::now();
		auto diff = end - start;
		cout << "Время вычисления: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;

		start = chrono::steady_clock::now();
		newton(a[i].first, a[i].second, epsilon);
		end = chrono::steady_clock::now();
		diff = end - start;
		cout << "Время вычисления: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;

		start = chrono::steady_clock::now();
		newtonMod(a[i].first, a[i].second, epsilon);
		end = chrono::steady_clock::now();
		diff = end - start;
		cout << "Время вычисления: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;

		start = chrono::steady_clock::now();
		secant(a[i].first, a[i].second, epsilon);
		end = chrono::steady_clock::now();
		diff = end - start;
		cout << "Время вычисления: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;

	}


	return EXIT_SUCCESS;
}