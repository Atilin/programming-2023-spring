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
	//return 0.116 * x * x * (x - 0.033) + 2;
}

void makeChartReverse(double a, double b, int m, vector <pair <double, double>>& chart)
{
	for (int i = 0; i < m + 1; ++i)
	{
		pair <double, double> p;
		p.second = a + (b - a) / m * i;
		p.first = f(a + (b - a) / m * i);
		chart.push_back(p);
	}
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
	cout << endl << '\t' << "f(x):" << '\t' << '\t' << '\t' << '\t' << "x:" << endl;

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

void separation(double A, double B, double N, vector <pair <double, double>>& a, vector <pair <double, double>> c, int n, double F)
{
	a.erase(a.begin(), a.end());
	double h = (B - A) / N;
	double counter = 0;
	double x1 = A;
	double x2 = x1 + h;
	double y1 = newton(c, n, x1) - F;
	double y2 = 0;

	while (x2 <= B)
	{
		y2 = newton(c, n, x2) - F;

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

void bisection(double a, double b, double e, vector <pair <double, double>> c, int n, double F)
{
	cout << "МЕТОД БИСЕКЦИИ:" << endl;
	cout << "Начальное приближение к корню: " << (a + b) / 2 << endl;
	int k = 0;
	while ((b - a) > 2 * e)
	{
		double q = (a + b) / 2;

		if (newton(c, n, a) * newton(c, n, q) <= 0)
		{
			b = q;
		}
		else
		{
			a = q;
		}
		k++;
	}
	cout << "Конечное приближение к корню: " << (a + b) / 2 << endl;
	cout << "Точность: " << (b - a) / 2 << endl;
	cout << "Количество шагов: " << k << endl;
	cout << "Абсолютная величина невязки: " << abs(f((a + b) / 2) - F) << endl;
}

void secant(double a, double b, double e, int n, vector <pair <double, double>> c, double F)
{
	cout << "МЕТОД СЕКУЩИХ:" << endl;

	double q = b - ((newton(c, n, b) - F) / (newton(c, n, b) - newton(c, n, a))) * (b - a);
	cout << "Начальное приближение к корню: " << q << endl;

	int k = 1;


	while (abs(b - q) > e)
	{
		double q_copy = q;
		q = b - ((newton(c, n, b) - F) / (newton(c, n, b) - newton(c, n, q_copy))) * (b - q_copy);
		b = q_copy;

		k++;
	}

	cout << "Конечное приближение к корню: " << q << endl;
	//cout << "Точность: " << abs(b - q) << endl;
	cout << "Количество шагов: " << k << endl;
	cout << "Абсолютная величина невязки: " << abs(f(q) - F) << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(15) << fixed;

	cout << "ЗАДАЧА ОБРАТНОГО ИНТЕРПОЛИРОВАНИЯ";
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
	vector <pair <double, double>> chart1;
	makeChartReverse(a, b, m, chart1);
	printChart(chart1);

	bool flag1 = 1;
	while (flag1 == 1)
	{
		cout << endl << "Введите F - точку обратного интерполирования: ";
		double x = 0;
		cin >> x;





		cout << endl << endl << "---------" << endl << "СПОСОБ 1:" << endl << "---------";

		cout << endl << "Таблица узлов, отсортированная в порядке удаления от точки интерполирования: ";
		sortChart(chart1, x);
		printChart(chart1);

		cout << endl << "Введите n - степень интерполяционного многочлена (n < " << m + 1 << "): ";
		int n = 0;
		cin >> n;
		while (n > m)
		{
			cout << endl << "Степень интерполяционного многочлена не должна превышать значение m == " << m << '.';
			cout << endl << "Введите n - степень интерполяционного многочлена (n < " << m + 1 << "): ";
			cin >> n;
		}

		cout << endl << "Значение интерполяционного многочлена, найденное при помощи представления в форме Ньютона: ";

		cout << newton(chart1, n, x);
		cout << endl << "Значение абсолютной фактической погрешности для формы Ньютона: ";
		cout << abs(f(newton(chart1, n, x)) - x);









		cout << endl << endl << "---------" << endl << "СПОСОБ 2:" << endl << "---------";

		vector <pair <double, double>> chart2;
		makeChart(a, b, m, chart2);

		double epsilon = 0;
		cout << "Задайте точность (epsilon): ";
		cin >> epsilon;
		cout << endl;

		//отделение корней

		vector <pair <double, double>> roots;
		double N = 0;
		bool flag = 0;
		while (flag == 0)
		{
			cout << "Задайте число N деления на отрезки: " << endl;
			cin >> N;

			separation(a, b, N, roots, chart2, n, x);
			cout << endl;

			cout << "Вас устраивает полученный результат? Если да - введите 1, иначе - 0" << endl;

			cin >> flag;
			cout << endl;
		}

		//уточнение корней, бисекция

		for (int i = 0; i < roots.size(); ++i)
		{
			cout << "-------------------------------------" << endl;
			cout << i + 1 << " корень:" << endl << endl;
			//bisection(roots[i].first, roots[i].second, epsilon, chart2, n, x);
			secant(roots[i].first, roots[i].second, epsilon, n, chart2, x);
		}





		cout << endl << endl << "Желаете ввести новые значения F и n? (1 - Да, 0 - Нет)    ";
		cin >> flag1;

	}


	return EXIT_SUCCESS;
}