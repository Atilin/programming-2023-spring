#include <iostream>
#include <clocale>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

double f(double x)
{
	return pow(2.7182818284590451, 1.5 * 4 * x);
}

double f1(double x)
{
	return 6 * pow(2.7182818284590451, 1.5 * 4 * x);
}

double f2(double x)
{
	return 6 * 6 * pow(2.7182818284590451, 1.5 * 4 * x);
}

void makeChart(double a, double h, int m, vector <vector <double>>& chart)
{
	for (int i = 0; i < m + 1; ++i)
	{
		chart[0].push_back(a + h * i);
		chart[1].push_back(f(a + h * i));
		chart[2].push_back(0.0);
		chart[3].push_back(0.0);
		chart[4].push_back(0.0);
		chart[5].push_back(0.0);
	}
}

void printChart(vector <vector <double>> chart, int m)
{
	cout << endl << '\t' << "x:" << '\t' << '\t' << '\t' << "f(x):" << '\t' << '\t' << '\t' << "f'(x)_÷ä:" << '\t' << '\t' << "|f'(x)_ò - f'(x)_÷ä|:" << '\t' << "f''(x)_÷ä:" << '\t' << '\t' << "|f''(x)_ò - f''(x)_÷ä|:" << endl;

	for (int i = 0; i < m + 1; ++i)
	{
		cout << i + 1 << ") " << '\t' << chart[0][i] << '\t' << chart[1][i] << '\t' << chart[2][i] << '\t' << chart[3][i] << '\t' << chart[4][i] << '\t' << chart[5][i] << endl;
	}
}

void fillThirdColoumn(vector <vector <double>>& chart, int m, double h)
{
	for (int i = 0; i < m - 1; ++i)
	{
		chart[2][i] = (-3 * chart[1][i] + 4 * chart[1][i + 1] - chart[1][i + 2]) / 2 / h;
	}
	for (int i = m - 1; i < m + 1; ++i)
	{
		chart[2][i] = (3 * chart[1][i] - 4 * chart[1][i - 1] + chart[1][i - 2]) / 2 / h;
	}
}

void fillFourthColoumn(vector <vector <double>>& chart, int m)
{
	for (int i = 0; i < m + 1; ++i)
	{
		chart[3][i] = abs(f1(chart[0][i]) - chart[2][i]);
	}
}

void fillFifthColoumn(vector <vector <double>>& chart, int m, double h)
{
	for (int i = 1; i < m; ++i)
	{
		chart[4][i] = (chart[1][i + 1] - 2 * chart[1][i] + chart[1][i - 1]) / h / h;
	}
}

void fillSixthColoumn(vector <vector <double>>& chart, int m)
{
	for (int i = 1; i < m; ++i)
	{
		chart[5][i] = abs(f2(chart[0][i]) - chart[4][i]);
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(15) << fixed;

	cout << "ÇÀÄÀ×À ÍÀÕÎÆÄÅÍÈß ÏÐÎÈÇÂÎÄÍÛÕ ÒÀÁËÈ×ÍÎ-ÇÀÄÀÍÍÎÉ ÔÓÍÊÖÈÈ ÏÎ ÔÎÐÌÓËÀÌ ×ÈÑËÅÍÍÎÃÎ ÄÈÔÔÅÐÅÍÖÈÐÎÂÀÍÈß";
	cout << endl << endl << "Âàðèàíò 8:   f(x) = e ^ (1.5 * 4 * x)";


	bool flag2 = 1;
	while (flag2 == 1)
	{
		cout << endl << endl << "Ââåäèòå ÷èñëî çíà÷åíèé â òàáëèöå (m+1): ";
		int m = 0;
		cin >> m;
		m--;

		cout << endl << "Ââåäèòå íà÷àëî îòðåçêà: ";
		double a = 0;
		cin >> a;

		double h = 0;
		bool flag1 = 0;
		while (flag1 == 0)
		{
			cout << endl << "Ââåäèòå øàã (h > 0): ";
			cin >> h;

			if (h > 0)
			{
				flag1 = 1;
			}
		}

		vector <vector <double>> chart(6);
		makeChart(a, h, m, chart);

		fillThirdColoumn(chart, m, h);

		fillFourthColoumn(chart, m);

		fillFifthColoumn(chart, m, h);

		fillSixthColoumn(chart, m);

		printChart(chart, m);


		cout << endl << endl << "ÆÅËÀÅÒÅ ÂÂÅÑÒÈ ÍÎÂÛÅ ÄÀÍÍÛÅ? (1 - äà, 0 - íåò):     ";
		cin >> flag2;
	}

	return EXIT_SUCCESS;
}