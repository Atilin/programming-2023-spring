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

	cout << "����������� ���������� ��������� �� ������������ ��������" << endl << endl;


	cout << "f(x) = sin(x) - x / 2" << endl << endl;
	cout << "������� ������� ��������������:" << endl;
	cout << "����� �������: ";
	double a;
	cin >> a;
	cout << "������ �������: ";
	double b;
	cin >> b;

	double exact_value = f_i(b) - f_i(a);
	cout << endl << "������ �������� ��������� ������� f(x): " << exact_value << endl;

	double left = f(a) * (b - a);
	cout << "�� ������ ��������������: " << left << endl;

	double right = f(b) * (b - a);
	cout << "�� ������� ��������������: " << right << endl;

	double mid = f((b + a) / 2) * (b - a);
	cout << "�� �������� ��������������: " << mid << endl;

	double trapeze = (f(a) + f(b)) * (b - a) / 2;
	cout << "�� ��������: " << trapeze << endl;

	double simpson = (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6;
	cout << "�� ��������: " << simpson << endl;

	double h = (b - a) / 3;
	double three_eight = (f(a) / 8 + f(a + h) * 3 / 8 + f(a + 2 * h) * 3 / 8 + f(b) / 8) * (b - a);
	cout << "�� 3/8: " << three_eight << endl << endl;



	cout << "���������� ����������� ����������� �� ������ ��������������: " << abs(left - exact_value) << endl;

	cout << "���������� ����������� ����������� �� ������� ��������������: " << abs(right - exact_value) << endl;

	cout << "���������� ����������� ����������� �� �������� ��������������: " << abs(mid - exact_value) << endl;

	cout << "���������� ����������� ����������� �� ��������: " << abs(trapeze - exact_value) << endl;

	cout << "���������� ����������� ����������� �� ��������: " << abs(simpson - exact_value) << endl;

	cout << "���������� ����������� ����������� �� 3/8: " << abs(three_eight - exact_value) << endl << endl;

	cout << "------------------------------------------------------------------" << endl << endl;



	cout << "������������ �� �����������:" << endl << endl;

	cout << "f(x) = 5" << endl;
	double exact_value0 = f0_i(b) - f0_i(a);

	double left0 = f0(a) * (b - a);
	cout << "�� ������ ��������������: " << left0 << endl;
	cout << "���������� ����������� ����������� �� ������ ��������������: " << abs(left0 - exact_value0) << endl;

	double right0 = f0(b) * (b - a);
	cout << "�� ������� ��������������: " << right0 << endl;
	cout << "���������� ����������� ����������� �� ������� ��������������: " << abs(right0 - exact_value0) << endl;

	double mid0 = f0((b + a) / 2) * (b - a);
	cout << "�� �������� ��������������: " << mid0 << endl;
	cout << "���������� ����������� ����������� �� �������� ��������������: " << abs(mid0 - exact_value0) << endl;

	double trapeze0 = (f0(a) + f0(b)) * (b - a) / 2;
	cout << "�� ��������: " << trapeze0 << endl;
	cout << "���������� ����������� ����������� �� ��������: " << abs(trapeze0 - exact_value0) << endl;

	double simpson0 = (f0(a) + 4 * f0((a + b) / 2) + f0(b)) * (b - a) / 6;
	cout << "�� ��������: " << simpson0 << endl;
	cout << "���������� ����������� ����������� �� ��������: " << abs(simpson0 - exact_value0) << endl;

	double three_eight0 = (f0(a) / 8 + f0(a + h) * 3 / 8 + f0(a + 2 * h) * 3 / 8 + f0(b) / 8) * (b - a);
	cout << "�� 3/8: " << three_eight0 << endl;
	cout << "���������� ����������� ����������� �� 3/8: " << abs(three_eight0 - exact_value0) << endl << endl;



	cout << "f(x) = x-2" << endl;
	double exact_value1 = f1_i(b) - f1_i(a);

	double left1 = f1(a) * (b - a);
	cout << "�� ������ ��������������: " << left1 << endl;
	cout << "���������� ����������� ����������� �� ������ ��������������: " << abs(left1 - exact_value1) << endl;

	double right1 = f1(b) * (b - a);
	cout << "�� ������� ��������������: " << right1 << endl;
	cout << "���������� ����������� ����������� �� ������� ��������������: " << abs(right1 - exact_value1) << endl;

	double mid1 = f1((b + a) / 2) * (b - a);
	cout << "�� �������� ��������������: " << mid1 << endl;
	cout << "���������� ����������� ����������� �� �������� ��������������: " << abs(mid1 - exact_value1) << endl;

	double trapeze1 = (f1(a) + f1(b)) * (b - a) / 2;
	cout << "�� ��������: " << trapeze1 << endl;
	cout << "���������� ����������� ����������� �� ��������: " << abs(trapeze1 - exact_value1) << endl;

	double simpson1 = (f1(a) + 4 * f1((a + b) / 2) + f1(b)) * (b - a) / 6;
	cout << "�� ��������: " << simpson1 << endl;
	cout << "���������� ����������� ����������� �� ��������: " << abs(simpson1 - exact_value1) << endl;

	double three_eight1 = (f1(a) / 8 + f1(a + h) * 3 / 8 + f1(a + 2 * h) * 3 / 8 + f1(b) / 8) * (b - a);
	cout << "�� 3/8: " << three_eight1 << endl;
	cout << "���������� ����������� ����������� �� 3/8: " << abs(three_eight1 - exact_value1) << endl << endl;



	cout << "f(x) = x ^ 2 + 4 * x + 3" << endl;
	double exact_value2 = f2_i(b) - f2_i(a);

	double left2 = f2(a) * (b - a);
	cout << "�� ������ ��������������: " << left2 << endl;
	cout << "���������� ����������� ����������� �� ������ ��������������: " << abs(left2 - exact_value2) << endl;

	double right2 = f2(b) * (b - a);
	cout << "�� ������� ��������������: " << right2 << endl;
	cout << "���������� ����������� ����������� �� ������� ��������������: " << abs(right2 - exact_value2) << endl;

	double mid2 = f2((b + a) / 2) * (b - a);
	cout << "�� �������� ��������������: " << mid2 << endl;
	cout << "���������� ����������� ����������� �� �������� ��������������: " << abs(mid2 - exact_value2) << endl;

	double trapeze2 = (f2(a) + f2(b)) * (b - a) / 2;
	cout << "�� ��������: " << trapeze2 << endl;
	cout << "���������� ����������� ����������� �� ��������: " << abs(trapeze2 - exact_value2) << endl;

	double simpson2 = (f2(a) + 4 * f2((a + b) / 2) + f2(b)) * (b - a) / 6;
	cout << "�� ��������: " << simpson2 << endl;
	cout << "���������� ����������� ����������� �� ��������: " << abs(simpson2 - exact_value2) << endl;

	double three_eight2 = (b - a) * (f2(a) / 8 + f2(a + h) * 3 / 8 + f2(a + 2 * h) * 3 / 8 + f2(b) / 8);
	cout << "�� 3/8: " << three_eight2 << endl;
	cout << "���������� ����������� ����������� �� 3/8: " << abs(three_eight2 - exact_value2) << endl << endl;



	cout << "f(x) = x ^ 3 + 7 * x ^ 2 + 4 * x - 1" << endl;
	double exact_value3 = f3_i(b) - f3_i(a);
	cout << exact_value3 << endl;

	double left3 = f3(a) * (b - a);
	cout << "�� ������ ��������������: " << left3 << endl;
	cout << "���������� ����������� ����������� �� ������ ��������������: " << abs(left3 - exact_value3) << endl;

	double right3 = f3(b) * (b - a);
	cout << "�� ������� ��������������: " << right3 << endl;
	cout << "���������� ����������� ����������� �� ������� ��������������: " << abs(right3 - exact_value3) << endl;

	double mid3 = f3((b + a) / 2) * (b - a);
	cout << "�� �������� ��������������: " << mid3 << endl;
	cout << "���������� ����������� ����������� �� �������� ��������������: " << abs(mid3 - exact_value3) << endl;

	double trapeze3 = (f3(a) + f3(b)) * (b - a) / 2;
	cout << "�� ��������: " << trapeze3 << endl;
	cout << "���������� ����������� ����������� �� ��������: " << abs(trapeze3 - exact_value3) << endl;

	double simpson3 = (f3(a) + 4 * f3((a + b) / 2) + f3(b)) * (b - a) / 6;
	cout << "�� ��������: " << simpson3 << endl;
	cout << "���������� ����������� ����������� �� ��������: " << abs(simpson3 - exact_value3) << endl;

	double h3 = (b - a) / 3;
	double three_eight3 = (b - a) * (f3(a) / 8 + f3(a + h3) * 3 / 8 + f3(a + 2 * h3) * 3 / 8 + f3(b) / 8);
	cout << "�� 3/8: " << three_eight3 << endl;
	cout << "���������� ����������� ����������� �� 3/8: " << abs(three_eight3 - exact_value3) << endl << endl;


	return EXIT_SUCCESS;
}