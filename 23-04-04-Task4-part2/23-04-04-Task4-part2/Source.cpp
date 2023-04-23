#define _USE_MATH_DEFINES
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

//double f(double x)
//{
//	return sin(x) - x / 2;
//}
//double f_i(double x)
//{
//	return -x * x / 4 - cos(x);
//}

double f(double x)
{
	return pow(M_E, 2 * x);
}
double f_i(double x)
{
	return pow(M_E, 2 * x) / 2;
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

	cout << "����������� ���������� ��������� �� ��������� ������������ ��������" << endl << endl;


	//cout << "f(x) = sin(x) - x / 2" << endl << endl;
	cout << "f(x) = e^(2*x)" << endl << endl;

	cout << "������� ������� ��������������:" << endl;
	cout << "����� �������: ";
	double a;
	cin >> a;
	cout << "������ �������: ";
	double b;
	cin >> b;

	cout << "������� ����� ����������� ������� ������� [" << a << ", " << b << "]: ";
	double m = 0;
	cin >> m;

	double h = 0;
	h = (b - a) / m;
	cout << endl << "h = " << h << endl << endl;


	double exact_value = f_i(b) - f_i(a);
	cout << endl << "������ �������� ��������� ������� f(x): " << exact_value << endl;
	cout << "------------------------------------------------------------------" << endl;

	double w = 0;
	for (int j = 1; j <= m - 1; ++j)
	{
		w += f(a + j * h);
	}

	double q = 0;
	for (int j = 0; j <= m - 1; ++j)
	{
		q += f(a + j * h + h / 2);
	}

	double z = 0;
	z = f(a) + f(b);

	double left = h * (f(a) + w);
	cout << "��� ������ ��������������: " << left << endl;

	double right = h * (w + f((a + b) / 2));
	cout << "��� ������� ��������������: " << right << endl;

	double mid = h * q;
	cout << "��� �������� ��������������: " << mid << endl;

	double trapeze = h * (z + 2 * w) / 2;
	cout << "��� ��������: " << trapeze << endl;

	double simpson = h * (z + 2 * w + 4 * q) / 6;
	cout << "��� ��������: " << simpson << endl;



	cout << "------------------------------------------------------------------" << endl;

	cout << "���������� ����������� ����������� ��� ������ ��������������: " << abs(left - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� ������� ��������������: " << abs(right - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� �������� ��������������: " << abs(mid - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� ��������: " << abs(trapeze - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� ��������: " << abs(simpson - exact_value) << endl;

	cout << "------------------------------------------------------------------" << endl;

	//cout << "������� ������������� ����������� ��������� ��� ������� e^(2*x)" << endl;

	cout << "������������� ����������� ��� ������ ��������������: " << pow(M_E, 2 * b) * 2 / 2 * (b - a) * pow(h, 0 + 1) << endl;

	cout << "������������� ����������� ��� ������� ��������������: " << pow(M_E, 2 * b) * 2 / 2 * (b - a) * pow(h, 0 + 1) << endl;

	cout << "������������� ����������� ��� �������� ��������������: " << pow(M_E, 2 * b) * 4 / 24 * (b - a) * pow(h, 1 + 1) << endl;

	cout << "������������� ����������� ��� ��������: " << pow(M_E, 2 * b) * 4 / 12 * (b - a) * pow(h, 1 + 1) << endl;

	cout << "������������� ����������� ��� ��������: " << pow(M_E, 2 * b) * 16 / 2880 * (b - a) * pow(h, 3 + 1) << endl << endl << endl << endl;



	cout << "��������:" << endl << endl;



	cout << "f(x) = 5" << endl;

	double exact_value0 = f0_i(b) - f0_i(a);

	double w0 = 0;
	for (int j = 1; j <= m - 1; ++j)
	{
		w0 += f0(a + j * h);
	}

	double q0 = 0;
	for (int j = 0; j <= m - 1; ++j)
	{
		q0 += f0(a + j * h + h / 2);
	}

	double z0 = 0;
	z0 = f0(a) + f0(b);

	double left0 = h * (f0(a) + w0);
	cout << "��� ������ ��������������: " << left0 << endl;
	cout << "���������� ����������� ����������� ��� ������ ��������������: " << abs(left0 - exact_value0) << endl;

	double right0 = h * (w0 + f0((a + b) / 2));
	cout << "��� ������� ��������������: " << right0 << endl;
	cout << "���������� ����������� ����������� ��� ������� ��������������: " << abs(right0 - exact_value0) << endl << endl;



	cout << "f(x) = x-2" << endl;

	double exact_value1 = f1_i(b) - f1_i(a);

	double w1 = 0;
	for (int j = 1; j <= m - 1; ++j)
	{
		w1 += f1(a + j * h);
	}

	double q1 = 0;
	for (int j = 0; j <= m - 1; ++j)
	{
		q1 += f1(a + j * h + h / 2);
	}

	double z1 = 0;
	z1 = f1(a) + f1(b);

	double mid1 = h * q1;
	cout << "��� �������� ��������������: " << mid1 << endl;
	cout << "���������� ����������� ����������� ��� �������� ��������������: " << abs(mid1 - exact_value1) << endl;

	double trapeze1 = h / 2 * (z1 + 2 * w1);
	cout << "��� ��������: " << trapeze1 << endl;
	cout << "���������� ����������� ����������� ��� ��������: " << abs(trapeze1 - exact_value1) << endl << endl;



	cout << "f(x) = x ^ 2 + 4 * x + 3" << endl;

	double exact_value2 = f2_i(b) - f2_i(a);

	double w2 = 0;
	for (int j = 1; j <= m - 1; ++j)
	{
		w2 += f2(a + j * h);
	}

	double q2 = 0;
	for (int j = 0; j <= m - 1; ++j)
	{
		q2 += f2(a + j * h + h / 2);
	}

	double z2 = 0;
	z2 = f2(a) + f2(b);

	double simpson2 = h / 6 * (z2 + 2 * w2 + 4 * q2);
	cout << "��� ��������: " << simpson2 << endl;
	cout << "���������� ����������� ����������� ��� ��������: " << abs(simpson2 - exact_value2) << endl << endl;



	cout << "f(x) = x ^ 3 + 7 * x ^ 2 + 4 * x - 1" << endl;

	double exact_value3 = f3_i(b) - f3_i(a);

	double w3 = 0;
	for (int j = 1; j <= m - 1; ++j)
	{
		w3 += f3(a + j * h);
	}

	double q3 = 0;
	for (int j = 0; j <= m - 1; ++j)
	{
		q3 += f3(a + j * h + h / 2);
	}

	double z3 = 0;
	z3 = f3(a) + f3(b);

	double simpson3 = h / 6 * (z3 + 2 * w3 + 4 * q3);

	cout << "��� ��������: " << simpson3 << endl;
	cout << "���������� ����������� ����������� ��� ��������: " << abs(simpson3 - exact_value3) << endl << endl << endl << endl;





	cout << "��������� m � l ��� (������� l): ";
	double l = 0;
	cin >> l;
	cout << endl;

	double hl = (b - a) / m / l;

	double wl = 0;
	for (int j = 1; j <= m * l - 1; ++j)
	{
		wl += f(a + j * hl);
	}

	double ql = 0;
	for (int j = 0; j <= m * l - 1; ++j)
	{
		ql += f(a + j * hl + hl / 2);
	}

	//double z = 0;
	//z = f(a) + f(b);

	double left_l = hl * (f(a) + wl);
	cout << "��� ������ �������������� ��� ������������ ����� ���������: " << left_l << endl;

	double right_l = hl * (wl + f((a + b) / 2));
	cout << "��� ������� �������������� ��� ������������ ����� ���������: " << right_l << endl;

	double mid_l = hl * ql;
	cout << "��� �������� �������������� ��� ������������ ����� ���������: " << mid_l << endl;

	double trapeze_l = hl * (z + 2 * wl) / 2;
	cout << "��� �������� ��� ������������ ����� ���������: " << trapeze_l << endl;

	double simpson_l = hl * (z + 2 * wl + 4 * ql) / 6;
	cout << "��� �������� ��� ������������ ����� ���������: " << simpson_l << endl;

	cout << "------------------------------------------------------------------" << endl;

	cout << "���������� ����������� ����������� ��� ������ �������������� ��� ������������ ����� ���������: " << abs(left_l - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� ������� �������������� ��� ������������ ����� ���������: " << abs(right_l - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� �������� �������������� ��� ������������ ����� ���������: " << abs(mid_l - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� �������� ��� ������������ ����� ���������: " << abs(trapeze_l - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� �������� ��� ������������ ����� ���������: " << abs(simpson_l - exact_value) << endl;

	cout << "------------------------------------------------------------------" << endl;

	double left_exact = (pow(l, 0 + 1) * left_l - left) / (pow(l, 0 + 1) - 1);
	cout << "��������� �� ������ ����� ��� ��� ������ ��������������: " << left_exact << endl;

	double right_exact = (pow(l, 0 + 1) * right_l - right) / (pow(l, 0 + 1) - 1);
	cout << "��������� �� ������ ����� ��� ��� ������� ��������������: " << right_exact << endl;

	double mid_exact = (pow(l, 1 + 1) * mid_l - mid) / (pow(l, 1 + 1) - 1);
	cout << "��������� �� ������ ����� ��� ��� �������� ��������������: " << mid_exact << endl;

	double trapeze_exact = (pow(l, 1 + 1) * trapeze_l - trapeze) / (pow(l, 1 + 1) - 1);
	cout << "��������� �� ������ ����� ��� ��� ��������: " << trapeze_exact << endl;

	double simpson_exact = (pow(l, 3 + 1) * simpson_l - simpson) / (pow(l, 3 + 1) - 1);
	cout << "��������� �� ������ ����� ��� ��� ��������: " << simpson_exact << endl;

	cout << "------------------------------------------------------------------" << endl;

	cout << "���������� ����������� ����������� ��� ������ �������������� ��� ����������� ��������: " << abs(left_exact - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� ������� �������������� ��� ����������� ��������: " << abs(right_exact - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� �������� �������������� ��� ����������� ��������: " << abs(mid_exact - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� �������� ��� ����������� ��������: " << abs(trapeze_exact - exact_value) << endl;

	cout << "���������� ����������� ����������� ��� �������� ��� ����������� ��������: " << abs(simpson_exact - exact_value) << endl;


	return EXIT_SUCCESS;
}