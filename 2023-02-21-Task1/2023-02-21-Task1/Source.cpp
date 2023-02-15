#include <iostream>
#include <locale.h>
#include <cmath>
#include <vector>

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

void improvement(double a, double b, double e)
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

	//уточнение корней

	for (int i = 0; i < a.size(); ++i)
	{
		cout << i + 1 << " корень:" << endl;
		improvement(a[i].first, a[i].second, epsilon);
		cout << endl;
	}

	return EXIT_SUCCESS;
}