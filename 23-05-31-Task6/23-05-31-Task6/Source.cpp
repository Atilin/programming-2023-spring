#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

double F(double x)//точное решение з. Коши
{
	return (1 / (exp(x) + 1));
}

double f(double y)
{
	return (-y + y * y);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(15) << fixed;
	cout << "ЗАДАЧА 6: ЧИСЛЕННОЕ РЕШЕНИЕ ЗАДАЧИ КОШИ. ВАРИАНТ 8" << endl << "y'(x) = -y(x) + (y(x))^2" << endl;
	//cout << tgamma(1);

	bool flag = 1;
	while (flag == 1)
	{
		int N;
		cout << "Введите N = ";
		cin >> N;

		double h;
		cout << "Введите h = ";
		cin >> h;

		double x0 = 0;
		cout << "x0 = " << x0 << " (по условию)" << endl << endl;

		//1 - Найти точное решение тестовой задачи. Вывести на печать таблицу значений точного решения в равноотстоящих с шагом h точках х_k
		//cout << "Точное решение:" << endl;
		//cout << "x:\t\t\tf(x):" << endl;
		for (int k = -2; k <= N; k++)
		{
			//cout << x0 + k * h << "\t" << F(x0 + k * h) << endl;
		}
		cout << endl;

		//2 - Методом разложения в ряд Тейлора (можно ограничиться пятью-шестью ненулевыми слагаемыми) найти и вывести на печать значения приближённого решения в точках х_k
		//3 - Во всех точках x_k вывести на печать значения абсолютной погрешности метода разложения в ряд Тейлора.
		cout << "Метод разложения в ряд Тейлора:" << endl;
		//cout << "x:\t\t\tf(x):\t\t\tАбсолютная погрешность:" << endl;

		vector <double> Y;
		Y.push_back(0.5);//0
		Y.push_back(-0.25);//1
		Y.push_back(0);//2
		Y.push_back(0.125);//3
		Y.push_back(0);//4
		Y.push_back(-0.25);//5
		Y.push_back(0);//6
		Y.push_back(1.0625);//7
		Y.push_back(0);//8
		Y.push_back(-7.75);//9
		Y.push_back(0);//10

		/*for (int m = 0; m <= 5; m++)
		{
			cout << Y[m] << endl;
		}*/

		vector <double> Ad;//приближенные решения з. Коши в точках x_k = x_0 + k*h, где k = -2, -1, 0, 1, 2.

		for (int k = -2; k <= N; k++)//метод разложения в ряд Тейлора
		{
			double res = 0;
			for (int m = 0; m <= 10; m++)
			{
				res = res + (Y[m] * (pow(k * h, m))) / (tgamma(m + 1));
			}

			if (k < 3)//понадобится в методе Адамса
			{
				Ad.push_back(res);
			}

			//cout << x0 + k * h << "\t" << res << "\t" << abs(res - F(x0 + k * h)) << endl;
		}
		cout << endl;

		//4 - Используя начало таблицы построенное в п.2 (первые пять найденных Тейлором значений), вывести на печать значения приближённого решения, 
		//    полученного экстраполяционным методом Адамса 4 - го порядка в точках x_k = x_0 + k*h, где k = 3, 4, …, N.
		cout << "Метод Адамса:" << endl;
		//cout << "x:\t\t\tf(x):" << endl;

		/*for (int m = 0; m < 5; m++)
		{
			cout << Ad[m] << endl;
		}*/

		double res = 0;
		int m = 4;
		//cout << Ad[m] << endl;
		for (int k = 3; k <= N; k++)
		{
			res = Ad[m] + h * (f(Ad[m]) + 0.5 * (f(Ad[m]) - f(Ad[m - 1])) + 5 * (f(Ad[m]) + f(Ad[m - 2]) - 2 * f(Ad[m - 1])) / 12 + 0.375 * (f(Ad[m]) + 3 * f(Ad[m - 2]) - 3 * f(Ad[m - 1]) - f(Ad[m - 3])) + 251 * (f(Ad[m]) - 4 * f(Ad[m - 1]) + 6 * f(Ad[m - 2]) - 4 * f(Ad[m - 3]) + f(Ad[m - 4])) / 720);
			//cout << x0 + k * h << "\t" << res << endl;
			Ad.push_back(res);
			m = m + 1;
		}
		cout << "Абсолютная погрешность для последнего значения метода Адамса = " << abs(F(x0 + N * h) - res) << endl << endl;

		//5 - Методом Рунге-Кутта 4-го порядка найти и вывести на печать значения 
		//    приближённого решения в точках   x_k = x_0 + k*h, где k = 1, 2, …, N.
		cout << "Метод Рунге-Кутта:" << endl;
		//cout << "x:\t\t\tf(x):" << endl;

		double k1, k2, k3, k4;
		res = 0.5;
		for (int j = 1; j <= N; j++)
		{
			k1 = h * f(res);
			k2 = h * f(res + (k1) * 0.5);
			k3 = h * f(res + (k2) * 0.5);
			k4 = h * f(res + (k3) * 1);
			res = res + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

			//cout << x0 + j * h << "\t" << res << endl;
		}
		cout << "Абсолютная погрешность для последнего значения метода Рунге-Кутта = " << abs(F(x0 + N * h) - res) << endl << endl;
		
		//6 - Найти и вывести на печать значения приближенных решений исходной задачи, 
		//    полученных методом Эйлера, методом Эйлера I и методом Эйлера II в точках
		// 	  x_k = x_0 + k*h, где k = 1, 2, …, N
		cout << "Метод Эйлера:" << endl;
		//cout << "x:\t\t\tf(x):" << endl;
		res = 0.5;
		for (int j = 1; j <= N; j++)
		{
			res = res + h * f(res);
			//cout << x0 + j * h << "\t" << res << endl;
		}
		cout << "Абсолютная погрешность для последнего значения метода Эйлера = " << abs(F(x0 + N * h) - res) << endl << endl;
		

		cout << "Метод Эйлера 1:" << endl;
		//cout << "x:\t\t\tf(x):" << endl;
		res = 0.5;
		for (int j = 1; j <= N; j++)
		{
			res = res + h * f(res + h * f(res) / 2);
			//cout << x0 + j * h << "\t" << res << endl;
		}
		cout << "Абсолютная погрешность для последнего значения метода Эйлера 1 = " << abs(F(x0 + N * h) - res) << endl << endl;


		cout << "Метод Эйлера 2:" << endl;
		//cout << "x:\t\t\tf(x):" << endl;
		res = 0.5;
		for (int j = 1; j <= N; j++)
		{
			res = res + h * (f(res) + f(res + h * f(res))) / 2;
			//cout << x0 + j * h << "\t" << res << endl;
		}
		cout << "Абсолютная погрешность для последнего значения метода Эйлера 2 = " << abs(F(x0 + N * h) - res) << endl << endl;
		cout << endl;

		Y.clear();
		Ad.clear();

		cout << "Если хотите задать новые параметры, введите 1, иначе введите 0" << endl;
		cin >> flag;
	}
	return 0;
}