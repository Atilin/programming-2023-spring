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
			cout << "� ������� [" << x1 << ", " << x2 << "] ��� ������� ���� ������" << endl;

			pair <double, double> p;
			p.first = x1;
			p.second = x2;
			a.push_back(p);
		}

		x1 = x2;
		x2 = x1 + h;
		y1 = y2;
	}
	cout << "����� ������: " << counter << endl;
}

void bisection(double a, double b, double e)
{
	cout << "����� ��������:" << endl;
	cout << "��������� ����������� � �����: " << (a + b) / 2 << endl;
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
	cout << "�������� ����������� � �����: " << (a + b) / 2 << endl;
	cout << "��������: " << (b - a) / 2 << endl;
	cout << "���������� �����: " << k << endl;
	cout << "���������� �������� �������: " << abs(f((a + b) / 2)) << endl;
}

double f1(double x) // �����������
{
	return 0.3 - 4 * sin(x);
}

void newton(double a, double b, double e)
{
	cout << "����� �������:" << endl;

	double c = (a + b) / 2; // ������ �����������
	cout << "��������� ����������� � �����: " << c << endl;

	double d = c - f(c) / f1(c); // ������ �����������

	int k = 2;
	while (abs(d - c) > e)
	{
		c = d;
		d = c - f(c) / f1(c);

		k++;
	}
	cout << "�������� ����������� � �����: " << d << endl;
	cout << "��������: " << abs(d - c) << endl;
	cout << "���������� �����: " << k << endl;
	cout << "���������� �������� �������: " << abs(f(d)) << endl;
}

void newtonMod(double a, double b, double e)
{
	cout << "����� ������� ����������������:" << endl;

	double c = (a + b) / 2; // ������ �����������
	double x0 = c;
	cout << "��������� ����������� � �����: " << c << endl;

	double d = c - f(c) / f1(c); // ������ �����������

	int k = 2;
	while (abs(d - c) > e)
	{
		c = d;
		d = c - f(c) / f1(x0);

		k++;
	}
	cout << "�������� ����������� � �����: " << d << endl;
	cout << "��������: " << abs(d - c) << endl;
	cout << "���������� �����: " << k << endl;
	cout << "���������� �������� �������: " << abs(f(d)) << endl;
}

void secant(double a, double b, double e)
{
	cout << "����� �������:" << endl;

	double c = b - (f(b) / (f(b) - f(a))) * (b - a);
	cout << "��������� ����������� � �����: " << c << endl;

	int k = 1;


	while (abs(b - c) > e)
	{
		double c_copy = c;
		c = b - (f(b) / (f(b) - f(c_copy))) * (b - c_copy);
		b = c_copy;

		k++;
	}

	cout << "�������� ����������� � �����: " << c << endl;
	cout << "��������: " << abs(b - c) << endl;
	cout << "���������� �����: " << k << endl;
	cout << "���������� �������� �������: " << abs(f(c)) << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "��������� ������ ������� ���������� ��������� (����� ��������)" << endl << endl;

	cout << "������������� �������     4 * cos(x) + 0.3 * x" << endl << endl;

	double A = 0;
	cout << "������� ����� ����� (A) ��������� ������ ������: ";
	cin >> A;
	cout << endl;

	double B = 0;
	cout << "������� ������ ����� (B) ��������� ������ ������: ";
	cin >> B;
	cout << endl;

	double epsilon = 0;
	cout << "������� �������� (epsilon): ";
	cin >> epsilon;
	cout << endl;

	//��������� ������

	vector <pair <double, double>> a;
	double N = 0;
	bool flag = 0;
	while (flag == 0)
	{
		cout << "������� ����� N ������� �� �������: " << endl;
		cin >> N;

		separation(A, B, N, a);
		cout << endl;

		cout << "��� ���������� ���������� ���������? ���� �� - ������� 1, ����� - 0" << endl;

		cin >> flag;
		cout << endl;
	}

	//��������� ������, ��������

	for (int i = 0; i < a.size(); ++i)
	{
		cout << "-------------------------------------" << endl;
		cout << i + 1 << " ������:" << endl << endl;

		auto start = chrono::steady_clock::now();
		bisection(a[i].first, a[i].second, epsilon);
		auto end = chrono::steady_clock::now();
		auto diff = end - start;
		cout << "����� ����������: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;

		start = chrono::steady_clock::now();
		newton(a[i].first, a[i].second, epsilon);
		end = chrono::steady_clock::now();
		diff = end - start;
		cout << "����� ����������: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;

		start = chrono::steady_clock::now();
		newtonMod(a[i].first, a[i].second, epsilon);
		end = chrono::steady_clock::now();
		diff = end - start;
		cout << "����� ����������: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;

		start = chrono::steady_clock::now();
		secant(a[i].first, a[i].second, epsilon);
		end = chrono::steady_clock::now();
		diff = end - start;
		cout << "����� ����������: " << chrono::duration <double, milli>(diff).count() << " ms" << endl << endl;

	}


	return EXIT_SUCCESS;
}