#include <iostream>
#include <clocale>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

double f(double x)
{
	return 2 * sin(x) - x / 2;
	//return (x - 1.13) * x * x + 2 * x;
}



void makeChart(double a, double b, int m, vector <pair <double, double>>& chart)
{
	for (int i = 0; i < m + 1; ++i)
	{
		pair <double, double> p;
		p.first = a + (b - a) / m * i;
		p.second = f(a + (b - a) / m * i);
		chart.push_back(p);
	}
}

void printChart(vector <pair <double, double>> chart)
{
	cout << endl << '\t' << "x:" << '\t' << '\t' << '\t' << '\t' << "f(x):" << endl;

	for (int i = 0; i < chart.size(); ++i)
	{
		cout << i + 1 << ") " << '\t' << chart[i].first << '\t' << chart[i].second << endl;
	}
}

void sortChart(vector <pair <double, double>>& c, double x)
{
	double tmp1 = 0;
	double tmp2 = 0;
	for (int i = 0; i < c.size(); i++)
	{
		for (int j = (c.size() - 1); j >= (i + 1); j--)
		{
			if (abs(c[j].first - x) < abs(c[j - 1].first - x))
			{
				tmp1 = c[j].first;
				tmp2 = c[j].second;
				c[j].first = c[j - 1].first;
				c[j].second = c[j - 1].second;
				c[j - 1].first = tmp1;
				c[j - 1].second = tmp2;
			}
		}
	}
}

double recursion(vector <pair <double, double>> c, int m, int n)
{
	if (n - m == 1)
	{
		return (c[n].second - c[m].second) / (c[n].first - c[m].first);
	}
	else
	{
		return (recursion(c, m + 1, n) - recursion(c, m, n - 1)) / (c[n].first - c[m].first);
	}
}

double newton(vector <pair <double, double>> c, int n, double x)
{
	double ans = c[0].second;

	for (int i = 1; i <= n; ++i)
	{
		double s = recursion(c, 0, i);

		for (int j = 0; j < i; ++j)
		{
			s = s * (x - c[j].first);
		}

		ans = ans + s;
	}

	return ans;
}

double lagrange(vector <pair <double, double>> c, int n, double x)
{
	double ans = 0;

	for (int k = 0; k <= n; ++k)
	{
		double d = 1;

		for (int i = 0; i <= n; ++i)
		{
			if (i != k)
			{
				d = d * (x - c[i].first) / (c[k].first - c[i].first);
			}
		}

		d = d * c[k].second;

		ans = ans + d;
	}

	return ans;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(15) << fixed;

	cout << "ЗАДАЧА АЛГЕБРАИЧЕСКОГО ИНТЕРПОЛИРОВАНИЯ";
	cout << endl << endl << "Вариант 8:   f = 2 * sin(x) - x / 2";

	cout << endl << endl << "Введите число значений в таблице (m+1): ";
	int m = 0;
	cin >> m;
	m--;

	cout << endl << "Введите левый конец отрезка [a, b], из которого выбираются узлы интерполяции: ";
	double a = 0;
	cin >> a;

	cout << endl << "Введите правый конец отрезка [a, b], из которого выбираются узлы интерполяции: ";
	double b = 0;
	cin >> b;

	cout << endl << "Таблица узлов интерполяции: ";
	vector <pair <double, double>> chart;
	makeChart(a, b, m, chart);
	printChart(chart);

	bool flag = 1;
	while (flag == 1)
	{

		cout << endl << "Введите x - точку интерполирования: ";
		double x = 0;
		cin >> x;

		cout << endl << "Таблица узлов, отсортированная в порядке удаления от точки интерполирования: ";
		sortChart(chart, x);
		printChart(chart);

		cout << endl << "Введите n - степень интерполяционного многочлена: ";
		int n = 0;
		cin >> n;
		while (n > m)
		{
			cout << endl << "Степень интерполяционного многочлена не должна превышать значение m";
			cout << endl << "Введите n - степень интерполяционного многочлена: ";
			cin >> n;
		}

		cout << endl << "Значение интерполяционного многочлена, найденное при помощи представления в форме Ньютона: ";
		cout << newton(chart, n, x);
		cout << endl << "Значение абсолютной фактической погрешности для формы Ньютона: ";
		cout << abs(f(x) - newton(chart, n, x));

		cout << endl << endl << "Значение интерполяционного многочлена, найденное при помощи представления в форме Лагранжа: ";
		cout << lagrange(chart, n, x);
		cout << endl << "Значение абсолютной фактической погрешности для формы Лагранжа: ";
		cout << abs(f(x) - lagrange(chart, n, x));

		cout << endl << endl << "Желаете ввести новые значения х и n? (1 - Да, 0 - Нет)    ";
		cin >> flag;

	}

	return EXIT_SUCCESS;
}