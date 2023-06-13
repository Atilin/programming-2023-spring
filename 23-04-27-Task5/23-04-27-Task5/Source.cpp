#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

long double f(long double x)//������� ��� 5.1,5.3
{
	return sin(x);
}

long double ro(long double x)//��������� ��� 5.1, 5.3
{
	return exp(x);
}

double ro_Meler(double x)//��������� ��� �� ������ 5.2
{
	return 1 / sqrt(1 - x * x);
}

template <typename T1, typename T2, typename T3> //���������� �������� ���������� � �����
T3 polinom(T1 n, T2* p, T3 x)					//n-1  - ������� ����������, � - ������ �����, � - �����, � ������� ����������� �������� ����������
{
	double result = p[0];
	double tmp = 1;
	for (int i = 1; i < n; ++i)
	{
		tmp *= x;
		result += tmp * p[i];
	}
	return result;
}

//����� ������ - ����� ������� ������� �������� �������������� ��������� (����). ��� ����� ����������������� ���������� ����������,
//����� � ������� ������������ �������������� ������� ��������� ���������� � ������������ ������� ������������ ����,
//�� ������� ���������������, ������� � ��������� (�� ������), ��������� ��� ���������� �������
long double* Gauss_method(long double** c, int N)//� - ������� �������, N - ���������� ����� (�����)
{
	for (int i = 0; i < N; i++)//������ ��� (���������� ������� � ����������� �����)
	{
		long double tmp = c[i][i];
		for (int j = N; j >= i; j--)
			c[i][j] /= tmp;
		for (int j = i + 1; j < N; j++)
		{
			tmp = c[j][i];
			for (int k = N; k >= i; k--)
				c[j][k] -= tmp * c[i][k];
		}
	}

	long double* A = new long double[N];//�������� ��� (��������� ����������� ������)
	A[N - 1] = c[N - 1][N];
	for (int i = N - 2; i >= 0; i--)
	{
		A[i] = c[i][N];
		for (int j = i + 1; j < N; j++) A[i] -= c[i][j] * A[j];
	}

	return A;
}

//������ �������� ��������� (��������� ������������ ������� ������� ���������������)
long double CQF_for_func(double a, double b, long double (*func)(long double))//a,b - �������, func - ������������ �������, ���������� ������� �������� long double
{
	int n = 1000000;
	long double h = (b - a) / n;
	long double* z = new long double[n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		z[i] = a + i * h;
	}
	long double result = 0;
	for (int i = 0; i < n; ++i)
	{
		result += ro(z[i] + h / 2.0) * func(z[i] + h / 2.0);
	}
	result *= h;
	delete[] z;
	return result;
}

double func1(double x)//��� �� ������ (5.2)
{
	return cos(x * x);
}

double func2(double x)//��� �� ������ (5.2)
{
	return exp(x) * sin(x * x);
}

double P(int n, double x)//������������ ���������� ���������� ��������
{
	if (n == 0) return 1;
	if (n == 1) return x;
	return ((2 * (double)n - 1) / (double)n) * P(n - 1, x) * x - (((double)n - 1) / (double)n) * P(n - 2, x);
}

double P_der(int n, double x)//����������� ���������� ��������
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	return ((2 * (double)n - 1) / (double)n) * (P(n - 1, x) + P_der(n - 1, x) * x) - (((double)n - 1) / (double)n) * P_der(n - 2, x);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(18) << scientific;//scientific ���� ��������� ������ �������� � � ����� ��������� ��������

	int flag;
	cout << "������� ����� ������." << endl;
	cout << "1. ����������� ���������� ��������� � ������� ��� ����." << endl;
	cout << "2. ����������� ���������� ��������� ��� ������ �� ������ � ������." << endl;
	cout << "3. ����������� ���������� ��������� ��� ������ ��������� �� ������." << endl;
	cin >> flag;
	do {
		switch (flag)
		{
		case 1:
		{
			do {
				cout << endl << "---------------------------------------------------------------------------------------" << endl;
				cout << "����������� ���������� ��������� � ������� ���." << endl;
				cout << "---------------------------------------------------------------------------------------" << endl;
				cout << endl << "   f(x) = sin(x),    ro(x) = e^x " << endl << endl;

				double a;
				double b;
				cout << "������� ������� ��������������: " << endl;
				cin >> a >> b;

				int N;
				cout << "������� ����� �����: " << endl;
				cin >> N;

				long double* x = new long double[N]; //������ �����, ��������� �������
				do {
					flag = 0;
					cout << "������� ������� ��������� ����: " << endl;
					for (int i = 0; i < N; ++i)
					{
						cin >> x[i];
						for (int j = 0; j < i; ++j)
							if (x[i] == x[j])
							{
								flag = 1;
								break;
							}
						if (flag == 1)
						{
							cout << "������ �����! " << endl;
							break;
						}
					}
				} while (flag);

				int n = 100000;
				long double h = (b - a) / n;
				long double* z = new long double[n + 1]; //������ n+1 �������������� �����
				for (int i = 0; i < n + 1; ++i)
				{
					z[i] = a + i * h;
				}

				//���������� �������� (��������� ������������ ������� ������� ���������������)
				long double* m = new long double[2 * N]; //������ �������� ()
				for (int i = 0; i < 2 * N; ++i)//����� �������
				{
					long double result = 0;
					for (int j = 0; j < n; ++j)
					{
						long double tmp = ro(z[j] + h / 2.0);
						for (int k = 0; k < i; ++k)//���������� �� � � ������� �
						{
							tmp *= (z[j] + h / 2.0);
						}
						result += tmp;
					}

					m[i] = h * result;//h ��� ���� ����, ������� ��� �� ������
				}

				cout << endl << "�������:" << endl << endl;
				for (int i = 0; i < 2 * N; ++i)
					cout << "m[" << i << "] = " << m[i] << endl;

				//�������� � ������������� ������� �������
				long double** c = new long double* [N];//n �����
				for (int i = 0; i < N; i++)
					c[i] = new long double[N + 1];//n+1 �������

				for (int i = 0; i < N; ++i)//��������� ������� ��������� ������
				{
					for (int j = 0; j < N; ++j)
						c[i][j] = 1;
					c[i][N] = m[i];
				}

				for (int i = 1; i < N; ++i)//��������� ������������
				{
					for (int j = 0; j < N; ++j)
					{
						for (int k = 0; k < i; ++k)
							c[i][j] *= x[j];
					}
				}

				//������� ���� ������� ������
				long double* A = new long double[N];
				A = Gauss_method(c, N);//� - ������� �������, N - ���������� ����� (�����)

				cout << endl << "��������� ������������ ���: " << endl << endl;
				for (int i = 0; i < N; i++)
					cout << "A[" << i << "]=" << setw(27) << A[i] << " " << endl;//setw(27) �������� 27 �������� ��� A[i]

				//�������� �� ���������� ������� N-1
				cout << "���� ������ ��������� ��� �� ���������� ������� N-1, ������� 1 (����� - 0)." << endl;
				cin >> flag;
				if (flag) {
					srand(time(0));
					int* p = new int[N];//������� ������������ ������������ ����������
					for (int i = 0; i < N; ++i)
						p[i] = rand() % 50 + 1;

					long double J_p = 0;//�������� ��������� ����������� ����� �����
					for (int i = 0; i < N; ++i)
						J_p += A[i] * polinom(N, p, x[i]);

					long double I_p = 0;//������ �������� ����� �������
					for (int i = 0; i < N; ++i)
						I_p += p[i] * m[i];

					//������� ��� ��������� ���������, �� ������� ��������� ���
					cout << endl << "f(x) = ";
					cout << p[0] << " + ";
					for (int i = 1; i < N - 1; ++i)
						cout << p[i] << "*x^" << i << " + ";
					cout << p[N - 1] << "*x^" << N - 1 << endl << endl;

					//���������� � ���, ��� ��������� ������ (����������� �������)
					cout << "������ �������� ��������� �� ����������: " << I_p << endl;
					cout << "�������� ���������, ����������� �� ��� = " << J_p << endl;
					cout << "����������� �����������: " << fabs(J_p - I_p) << endl << endl;
					system("pause");
				}

				//������ �������� ��������� �� ������� sin(x) (�� ��� ������� ���������������)
				long double I = CQF_for_func(a, b, f);
				cout << endl << "������ �������� ��������� �� ������� sin(x): " << I << endl;

				//������������ �������� ��������� (�������� �� ������� �� ���)
				long double J = 0;
				for (int i = 0; i < N; ++i)
					J += A[i] * f(x[i]);

				cout << "�������� ���������, ����������� �� ���:      " << J << endl;
				cout << "����������� �����������: " << fabs(J - I) << endl << endl;
				system("pause");

				//�� ����
				cout << endl << "---------------------------------------------------------------------------------------" << endl;
				cout << "������������ ���������� ��������� � ������� ������." << endl;
				cout << "---------------------------------------------------------------------------------------" << endl;

				//������������� ������� �������
				for (int i = 0; i < N; ++i)
				{
					for (int j = 0; j < N; ++j)
					{
						c[i][j] = m[i + j];
					}
					c[i][N] = -m[i + N];
				}

				//������� �������
				long double* aa = new long double[N + 1];
				aa = Gauss_method(c, N);
				aa[N] = 1;

				//����� �������������� ����������
				cout << endl << "��������� ������������� ���������:" << endl;
				cout << "w(x) = ";
				cout << setprecision(3) << fixed;
				cout << aa[0] << ' ';
				for (int i = 1; i < N; ++i)
					cout << showpos << aa[i] << "x^" << noshowpos << i << ' ';//����� ������� "+"
				cout << "+ x^" << N << endl;

				//������� ��������� W = 0 ��� ���������� ����� ������������
				if (N == 1) {
					x[0] = -aa[0];
					cout << "x[0] = " << x[0] << endl;
				}
				else
					if (N == 2)
					{
						double sqrt_D = sqrt(aa[1] * aa[1] - 4 * aa[0]);
						x[0] = (-aa[1] + sqrt_D) / 2;
						x[1] = (-aa[1] - sqrt_D) / 2;
						cout << "x[0] = " << x[0] << endl << "x[1] = " << x[1] << endl;
					}
					else {
						//��������� ������
						int M = 10000;
						int counter = 0;
						long double h = (b - a) / M;
						long double x1 = a;
						long double x2 = a + h;
						long double y1 = polinom(N + 1, aa, x1);//������������� ���������
						long double y2;
						long double begin[100]{ 0 }, end[100]{ 0 };

						while (x2 <= b)
						{
							y2 = polinom(N + 1, aa, x2);
							if (y1 * y2 <= 0)
							{
								begin[counter] = x1;
								end[counter] = x2;
								++counter;
							}
							x1 = x2;
							x2 += h;
							y1 = y2;
						}
						for (int i = 0; i < N; ++i)
							x[i] = 0;

						//����� �������
						cout << endl << "��������� ����:" << endl << endl;
						long double temp = 0;
						double e = 1e-12;
						for (int i = 0; i < counter; ++i)
						{
							x1 = begin[i];
							x2 = end[i];
							while (fabs(x1 - x2) > e)
							{
								temp = x2;
								x2 = temp - polinom(N + 1, aa, temp) / (polinom(N + 1, aa, temp) - polinom(N + 1, aa, x1)) * (temp - x1);
								x1 = temp;
							}
							x[i] = x2;
							cout << setprecision(18) << scientific << "x[" << i << "] = " << x[i] << endl;
						}
					}

				//������������� ������� ��� ���������� ������������� A_�
				for (int i = 0; i < N; ++i)
				{
					for (int j = 0; j < N; ++j)
						c[i][j] = 1;
					c[i][N] = m[i];
				}

				for (int i = 1; i < N; ++i)
				{
					for (int j = 0; j < N; ++j)
					{
						for (int k = 0; k < i; ++k)
							c[i][j] *= x[j];
					}
				}
				//������� �������
				A = Gauss_method(c, N);

				cout << endl << "��������� ������������ �� ����: " << endl << endl;
				for (int i = 0; i < N; ++i)
					cout << "A[" << i << "] = " << A[i] << endl;

				//�������� �� ��������� ������� 2N-1
				cout << endl << "���� ������ ������� �������� ������� �� ���������, ������� 1 (����� - 0). " << endl;
				cin >> flag;
				if (flag)
				{
					long double J_p = 0;//��������, ����������� �� �� ���� �� ��������� ������� 2N-1
					long double tmp = 1;//� ������� ��� � � ������� 2N-1
					for (int i = 0; i < N; ++i)
					{
						tmp = 1;
						for (int j = 0; j < 2 * N - 1; ++j)//���������� � � ������� 2N-1
							tmp *= x[i];
						J_p += tmp * A[i];
					}

					cout << endl << "f(x) = x^" << 2 * N - 1 << endl << endl;
					cout << "������ �������� ��������� �� ���������: " << m[2 * N - 1] << endl;//���������� ��� ����� ������� =0
					cout << "��������, ����������� �� �� ����:       " << J_p << endl;
					cout << "����������� �����������: " << fabs(m[2 * N - 1] - J_p) << endl << endl;
					system("pause");

				}

				//��������� �������� ��������� �� ������� sin(x)
				J = 0;
				for (int i = 0; i < N; ++i)
					J += A[i] * f(x[i]);

				cout << endl;
				cout << "������ �������� ��������� �� ������� sin(x): " << I << endl;
				cout << "�������� ���������, ����������� �� �� ����:  " << J << endl;
				cout << "����������� �����������: " << fabs(I - J) << endl;

				delete[] x;
				delete[] m;
				delete[] z;
				delete[] A;
				for (int i = 0; i < N; ++i)
					delete[] c[i];
				delete[] c;

				cout << endl << "���� ������ �������� ��������� ������, ������� 1 (����� - 0)." << endl;
				cin >> flag;

			} while (flag);
			break;
		};
		case 2:
		{
			cout << "���� ������ ��������� �� ������, ������� 1 (����� - 0)." << endl;
			cin >> flag;
			if (flag) {
				double a{ -1 }, b{ 1 };//��� �� ������ ������� ������, �����������
				int N;

				cout << endl << "���������� ���������� ��� ������ �� ������." << endl << endl;
				cout << "      f(x) = cos(x^2),  ro(x) = 1 " << endl << endl;
				double** x = new double* [8];//�������� �������, � ������� ���������� ����
				double** A = new double* [8];//�������� �������, � ������� ���������� ������������
				for (int i = 0; i < 8; ++i) {
					x[i] = new double[8];//�������� ���� ��� ���������� ���������� ����� (�� ��� ������ �����������)
					A[i] = new double[8];//�������� ������������ ��� �������� ���������� ����� (�� ��� ������ �����������)
				}

				//������� ����� ���������� ��������
				for (int j = 0; j < 8; ++j) {

					cout << "-------------------------------------------------------------------------" << endl;
					cout << "                         N = " << j + 1 << endl;
					cout << "-------------------------------------------------------------------------" << endl;

					//��������� ������
					N = j + 1;
					int M = 10000;
					int counter = 0;
					double h = (b - a) / M;
					double x1 = a;
					double x2 = a + h;
					double y1 = P(N, x1);//��������� ��������
					double y2;
					double begin[100]{ 0 }, end[100]{ 0 };

					while (x2 <= b)
					{
						y2 = P(N, x2);
						if (y1 * y2 <= 0)
						{
							begin[counter] = x1;
							end[counter] = x2;
							++counter;
						}
						x1 = x2;
						x2 += h;
						y1 = y2;
					}

					//����� �������
					double temp = 0;
					double e = 1e-12;
					for (int i = 0; i < counter; ++i)
					{
						x1 = begin[i];
						x2 = end[i];
						while (fabs(x1 - x2) > e)
						{
							temp = x2;
							x2 = temp - P(N, temp) / (P(N, temp) - P(N, x1)) * (temp - x1);
							x1 = temp;
						}
						x[j][i] = x2;

					}

					//������� ������������
					for (int i = 0; i < N; ++i)
					{
						double tmp = P_der(N, x[j][i]);
						A[j][i] = 2.0 / ((1 - x[j][i] * x[j][i]) * tmp * tmp);//����� �_� (�������_5_������, �����2, ���3)
					}

					//�_� ��������� ����� 0, ��� ��� ��� ������ � ������� ������������
					//�_� ��� ��������� �_� �����, ��� ��� ��������� ��� �_� ����� ������������ �_� 
					cout << endl << "��������� ���� � ������������:" << endl << endl;
					cout << setprecision(18) << scientific;
					for (int i = 0; i < N; ++i)
					{
						if (i > 9)
							cout << "x[" << i << "] = " << setw(24) << x[j][i] << "     " << "A[" << i << "] = " << setw(24) << A[j][i] << endl;
						else
							cout << "x[" << i << "] = " << setw(25) << x[j][i] << "     " << "A[" << i << "] = " << setw(25) << A[j][i] << endl;
					}

					cout << endl << "�������� �� ���������� ������� " << 2 * N - 1 << ':' << endl;
					srand(time(0));
					int* p = new int[2 * N];
					for (int i = 0; i < 2 * N; ++i)
						p[i] = rand() % 101 - 50;

					//�������� �� �� ������
					double J_p = 0;
					for (int i = 0; i < N; ++i)
						J_p += A[j][i] * polinom(2 * N, p, x[j][i]);

					//������ �������� (����������� ���������)
					double I_p = 0;
					double aa = a;
					double bb = b;
					for (int i = 0; i < 2 * N; ++i)
					{
						I_p += (double)p[i] / (i + 1) * (bb - aa);
						aa *= a;
						bb *= b;
					}

					//������� ���������, �� ������� ��������� �� ������
					cout << endl << "f(x) = ";
					cout << p[0] << ' ';
					for (int i = 1; i < 2 * N - 1; ++i)
						cout << showpos << p[i] << "x^" << noshowpos << i << ' ';
					cout << showpos << p[2 * N - 1] << "x^" << noshowpos << 2 * N - 1 << endl << endl;

					cout << "������ �������� ��������� �� ����������: " << I_p << endl;
					cout << "�������� ���������, ����������� �� ��� = " << J_p << endl;
					cout << "����������� �����������: " << fabs(J_p - I_p) << endl << endl;
					system("pause");

				}

				//� �������� �� ������ ������� �.�. �����, �� ������ [-1,1]
				cout << "���� ������ ���������� ���� � ������������ ��, �������� �� ������, ��� N = 3, 6, 7, 8, ������� 1 (����� - 0)." << endl;
				cin >> flag;
				if (flag)
					do {
						double c, d;
						cout << endl << "������� ����� �������: " << endl;
						cin >> c >> d;

						int k[4]{ 2,5,6,7 };
						for (int j = 0; j < 4; ++j)
						{
							cout << "------------------------------------------------------------------" << endl;
							cout << "                 N = " << k[j] + 1 << endl;
							cout << "------------------------------------------------------------------" << endl;

							N = k[j] + 1;
							double* C = new double[N];//������ ������������� ��� �������� �� ������
							double* t = new double[N];//5.2 ����� �����
							////if (c != -1 || d != 1)
							//{
							for (int i = 0; i < N; ++i) {
								C[i] = A[k[j]][i] * (d - c) / 2;//� � � ���������� � "5.2_�����_�����"
								t[i] = (d - c) / 2 * x[k[j]][i] + (c + d) / 2;//� � � ���������� � "5.2_�����_�����"
							}
							//}

							cout << endl << "��������� ���� � ������������ ��, �������� �� ������:" << endl << endl;
							cout << setprecision(18) << scientific;
							for (int i = 0; i < N; ++i)
								cout << "x[" << i << "] = " << setw(25) << t[i] << "     " << "A[" << i << "] = " << setw(25) << C[i] << endl;

							//��������, ���������� � ������� �������� �� ������
							double J = 0;
							for (int i = 0; i < N; ++i)
								J += C[i] * func1(t[i]);

							cout << "�������� ��������� �� ������� cos(x^2) �� ������� [" << fixed << setprecision(2) << c << ", " << d << "]: " << setprecision(18) << J << endl;

							delete[] C;
							delete[] t;
							system("pause");
						}
						cout << "���� ������ �������� ����� �������, ������� 1 (����� - 0)." << endl;
						cin >> flag;
					} while (flag);

					for (int i = 0; i < 8; ++i)
					{
						delete[] x[i];
						delete[] A[i];
					}
					delete[] x;
					delete[] A;
			}

			cout << "���� ������ ��������� �� ������, ������� 1 (����� - 0)." << endl;
			cin >> flag;
			if (flag) {
				cout << "���������� ���������� ��� ������ �� ������." << endl << endl;
				cout << endl << "   f(x) = e^x * sin(x^2),   ro(x) = 1 / sqrt(1 - x^2)" << endl << endl;
				do {
					int N;
					int n[3];
					cout << "������� ��� �������� N, ��� ������� ���������� ����� �������� ��������� �� �� ������: " << endl;
					for (int i = 0; i < 3; ++i)
						cin >> n[i];// ������ ���������� ����� ��� ������� ����� ����� �������� ��������� �� �� ������
					double J[3]{ 0 };//�������� ��������� ��� ������ ����������� �����

					double pi = 4.0 * atan(1.0);
					for (int i = 0; i < 3; ++i)
					{
						cout << "------------------------------------------------------------------" << endl;
						cout << "                 N = " << n[i] << endl;
						cout << "------------------------------------------------------------------" << endl;

						N = n[i];
						double* x = new double[N + 1];
						double J_tmp = 0;

						cout << endl << "����: " << endl;
						for (int j = 1; j < N + 1; ++j)
						{
							x[j] = cos((2 * (double)j - 1) / (2 * (double)N) * pi);//�������_5_������_�����2
							J_tmp += func2(x[j]);//����� �������� �� �_� = pi/n (������� �� ������)

							if (i > 9)//��� ��������� ������
								cout << "x[" << j << "] = " << setw(24) << setprecision(18) << x[j] << endl;
							else
								cout << "x[" << j << "] = " << setw(25) << setprecision(18) << x[j] << endl;
						}
						cout << endl << "�����������: " << (pi / N) << endl;
						J_tmp *= (pi / N);
						J[i] = J_tmp;
						//cout << "���������� �������� ��������� : " << J << endl << endl;
						delete[] x;
						system("pause");
					}
					cout << endl;
					cout << " ���������� ����� | ���������� �������� ��������� " << endl;
					cout << "---------------------------------------------------" << endl;
					for (int i = 0; i < 3; ++i)
						cout << setw(18) << n[i] << '|' << setw(30) << J[i] << endl;

					cout << endl << "���� ������ �������� N, ������� 1 (����� - 0)." << endl;
					cin >> flag;
				} while (flag);
			}
			break;
		};
		case 3:
		{
			cout << endl << "������ƨ���� ���������� ��������� ��� ������ ��������� �� ������." << endl << endl;
			cout << "      f(x) = sin(x),     ro(x) = e^x" << endl << endl;
			double a{ -1 }, b{ 1 };
			double arr_c[20]{ 0 };//������ ����� �������
			double arr_d[20]{ 0 };//������ ������ �������
			int number_of_nodes[20]{ 0 };//������ ���������� �����
			int number_of_division_gaps[20]{ 0 };//������ ����������� �������
			double J[20]{ 0 };//������ �������� ���������
			int k = 0;//������� �������� (���� ����� ������������� ��� ������ ������� ������, �� � ��� ���������� ���������� ��������)

			do {
				++k;

				double c, d;
				cout << "������� ������� ��������������: " << endl;
				cin >> c >> d;
				arr_c[k - 1] = c;
				arr_d[k - 1] = d;

				int N;
				cout << "������� ����� �����: " << endl;
				cin >> N;
				number_of_nodes[k - 1] = N;

				int m;
				cout << "������� ����� ����������� ������� ������� ��������������: " << endl;
				cin >> m;
				number_of_division_gaps[k - 1] = m;

				double h = (d - c) / m;//���
				double* z = new double[m + 1];//������ �����
				for (int i = 0; i < m + 1; ++i)
					z[i] = c + h * i;

				//������� ������������ ��� ������� [-1,1]
				int M = 10000;
				int counter = 0;
				double delta = (b - a) / M;
				double x1 = a;
				double x2 = a + delta;
				double y1 = P(N, x1);
				double y2;
				double begin[100]{ 0 }, end[100]{ 0 };

				//������� ������� �������� ����� ��� ��� ��� ������� [-1,1]

				while (x2 <= b)
				{
					y2 = P(N, x2);
					if (y1 * y2 <= 0)
					{
						begin[counter] = x1;
						end[counter] = x2;
						++counter;
					}
					x1 = x2;
					x2 += delta;
					y1 = y2;
				}
				//����� ������� ��� ��������� ������ ��� ��� ��� ������� [-1,1]

				double* x = new double[N];
				double temp;
				double e = 1e-12;
				for (int i = 0; i < counter; ++i)
				{
					x1 = begin[i];
					x2 = end[i];
					while (fabs(x1 - x2) > e)
					{
						temp = x2;
						x2 = temp - P(N, temp) / (P(N, temp) - P(N, x1)) * (temp - x1);
						x1 = temp;
					}
					x[i] = x2;//������� ���� ��� ��� ��� ������� [-1,1]
				}

				//��������� ������������ � ������� ���������� �������� ��� ��� ��� ������� [-1,1]
				double* A = new double[N];
				for (int i = 0; i < N; ++i)
				{
					double tmp = P_der(N, x[i]);
					A[i] = 2.0 / ((1 - x[i] * x[i]) * tmp * tmp);
				}

				//����� ����� � ������������� ��� ������� [-1,1]
				cout << endl << "��������� ���� � ������������:" << endl << endl;
				cout << setprecision(18) << scientific;
				for (int i = 0; i < N; ++i)//����������� ��� � �����
				{
					if (i > 9)
						cout << "x[" << i << "] = " << setw(24) << x[i] << "     " << "A[" << i << "] = " << setw(24) << A[i] << endl;
					else
						cout << "x[" << i << "] = " << setw(25) << x[i] << "     " << "A[" << i << "] = " << setw(25) << A[i] << endl;
				}

				double new_J = 0;//� ������� - �������� ����������������� ��������� �� ������� ������ h
				double* t = new double[N];//������ ���������������� �����
				double tmp;
				for (int i = 0; i < m; ++i)//��������� �������� m ����������
				{
					tmp = (z[i] + z[i + 1]) / 2.0;//5.3 ����� �����
					for (int j = 0; j < N; ++j)
					{
						t[j] = h / 2.0 * x[j] + tmp;
						new_J += (h / 2.0) * A[j] * ro(t[j]) * f(t[j]);//phi=ro*f
					}
				}
				//new_J *= (h / 2.0);
				J[k - 1] = new_J;

				cout << endl << "     �������      |     N     |     m     |        �������� ���������       " << endl;
				cout << "-----------------------------------------------------------------------------------" << endl;
				for (int i = 0; i < k; ++i)
					cout << " [" << setw(6) << fixed << setprecision(2) << arr_c[i] << "," << setw(6) << arr_d[i] << "]  |" << setw(10) << number_of_nodes[i] << " |" << setw(10) << number_of_division_gaps[i] << " |" << setw(25) << setprecision(17) << J[i] << endl;

				delete[] z;
				delete[] x;
				delete[] t;
				delete[] A;

				cout << endl << "���� ������ �������� ��������� ������, ������� 1 (����� - 0)." << endl;
				cin >> flag;
			} while (flag && k < 20);
			break;
		};

		default:
			cout << "������������ ����! ������� ����� �� 1 �� 3." << endl;
		}

		cout << "������� ����� ������." << endl;
		cout << "1. ����������� ���������� ��������� ��� ������� ��� ����." << endl;
		cout << "2. ����������� ���������� ��������� ��� ������ �� ������ � ������." << endl;
		cout << "3. ����������� ���������� ��������� ��� ������ ��������� �� ������." << endl;
		cout << "���� ������ ��������� ������ ���������, ������� 0." << endl;
		cin >> flag;

	} while (flag);

	return EXIT_SUCCESS;
}