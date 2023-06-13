#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

long double f(long double x)//функция для 5.1,5.3
{
	return sin(x);
}

long double ro(long double x)//плотность для 5.1, 5.3
{
	return exp(x);
}

double ro_Meler(double x)//плотность для КФ Мелера 5.2
{
	return 1 / sqrt(1 - x * x);
}

template <typename T1, typename T2, typename T3> //вычисление значения многочлена в точке
T3 polinom(T1 n, T2* p, T3 x)					//n-1  - степень многочлена, р - массив коэфф, х - точка, в которой вычисляется значение многочлена
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

//Метод Гаусса - метод решения системы линейных алгебраических уравнений (СЛАУ). Это метод последовательного исключения переменных,
//когда с помощью элементарных преобразований система уравнений приводится к равносильной системе треугольного вида,
//из которой последовательно, начиная с последних (по номеру), находятся все переменные системы
long double* Gauss_method(long double** c, int N)//с - матрица системы, N - количество строк (узлов)
{
	for (int i = 0; i < N; i++)//прямой ход (приведение матрицы к треугольной форме)
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

	long double* A = new long double[N];//обратный ход (выражение неизвестных членов)
	A[N - 1] = c[N - 1][N];
	for (int i = N - 2; i >= 0; i--)
	{
		A[i] = c[i][N];
		for (int j = i + 1; j < N; j++) A[i] -= c[i][j] * A[j];
	}

	return A;
}

//точное значение интеграла (составная квадратурная формула средних прямоугольников)
long double CQF_for_func(double a, double b, long double (*func)(long double))//a,b - границы, func - передаваемая функция, аргументом которой является long double
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

double func1(double x)//для КФ Гаусса (5.2)
{
	return cos(x * x);
}

double func2(double x)//для КФ Мелера (5.2)
{
	return exp(x) * sin(x * x);
}

double P(int n, double x)//рекуррентное вычисление многочлена Лежандра
{
	if (n == 0) return 1;
	if (n == 1) return x;
	return ((2 * (double)n - 1) / (double)n) * P(n - 1, x) * x - (((double)n - 1) / (double)n) * P(n - 2, x);
}

double P_der(int n, double x)//производная многочлена Лежандра
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	return ((2 * (double)n - 1) / (double)n) * (P(n - 1, x) + P_der(n - 1, x) * x) - (((double)n - 1) / (double)n) * P_der(n - 2, x);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(18) << scientific;//scientific дает грамотную запись степеней и в общем численных значений

	int flag;
	cout << "Введите номер задачи." << endl;
	cout << "1. Приближённое вычисление интеграла с помощью ИКФ НАСТ." << endl;
	cout << "2. Приближённое вычисление интеграла при помощи КФ Гаусса и Мелера." << endl;
	cout << "3. Приближённое вычисление интеграла при помощи составной КФ Гаусса." << endl;
	cin >> flag;
	do {
		switch (flag)
		{
		case 1:
		{
			do {
				cout << endl << "---------------------------------------------------------------------------------------" << endl;
				cout << "Приближённое вычисление интеграла с помощью ИКФ." << endl;
				cout << "---------------------------------------------------------------------------------------" << endl;
				cout << endl << "   f(x) = sin(x),    ro(x) = e^x " << endl << endl;

				double a;
				double b;
				cout << "Введите пределы интегрирования: " << endl;
				cin >> a >> b;

				int N;
				cout << "Введите число узлов: " << endl;
				cin >> N;

				long double* x = new long double[N]; //массив узлов, введенных ручками
				do {
					flag = 0;
					cout << "Введите попарно различные узлы: " << endl;
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
							cout << "Ошибка ввода! " << endl;
							break;
						}
					}
				} while (flag);

				int n = 100000;
				long double h = (b - a) / n;
				long double* z = new long double[n + 1]; //массив n+1 равноотстоящих узлов
				for (int i = 0; i < n + 1; ++i)
				{
					z[i] = a + i * h;
				}

				//нахождение моментов (составная квадратурная формула средних прямоугольников)
				long double* m = new long double[2 * N]; //массив моментов ()
				for (int i = 0; i < 2 * N; ++i)//номер момента
				{
					long double result = 0;
					for (int j = 0; j < n; ++j)
					{
						long double tmp = ro(z[j] + h / 2.0);
						for (int k = 0; k < i; ++k)//домножение на х в степени к
						{
							tmp *= (z[j] + h / 2.0);
						}
						result += tmp;
					}

					m[i] = h * result;//h для всех одно, вынесем его за скобку
				}

				cout << endl << "Моменты:" << endl << endl;
				for (int i = 0; i < 2 * N; ++i)
					cout << "m[" << i << "] = " << m[i] << endl;

				//создание и инициализация матрицы системы
				long double** c = new long double* [N];//n строк
				for (int i = 0; i < N; i++)
					c[i] = new long double[N + 1];//n+1 столбец

				for (int i = 0; i < N; ++i)//заполняем столбец свободных членов
				{
					for (int j = 0; j < N; ++j)
						c[i][j] = 1;
					c[i][N] = m[i];
				}

				for (int i = 1; i < N; ++i)//заполняем коэффициенты
				{
					for (int j = 0; j < N; ++j)
					{
						for (int k = 0; k < i; ++k)
							c[i][j] *= x[j];
					}
				}

				//решение СЛАУ методом Гаусса
				long double* A = new long double[N];
				A = Gauss_method(c, N);//с - матрица системы, N - количество строк (узлов)

				cout << endl << "Найденные коэффициенты ИКФ: " << endl << endl;
				for (int i = 0; i < N; i++)
					cout << "A[" << i << "]=" << setw(27) << A[i] << " " << endl;//setw(27) выделяет 27 символов для A[i]

				//проверка на многочлене степени N-1
				cout << "Если хотите проверить ИКФ на многочлене степени N-1, введите 1 (иначе - 0)." << endl;
				cin >> flag;
				if (flag) {
					srand(time(0));
					int* p = new int[N];//создаем произвольные коэффициенты многочлена
					for (int i = 0; i < N; ++i)
						p[i] = rand() % 50 + 1;

					long double J_p = 0;//значение интеграла посчитанное через суммы
					for (int i = 0; i < N; ++i)
						J_p += A[i] * polinom(N, p, x[i]);

					long double I_p = 0;//точное значение через моменты
					for (int i = 0; i < N; ++i)
						I_p += p[i] * m[i];

					//выведем наш случайный многочлен, на котором тестируем ИКФ
					cout << endl << "f(x) = ";
					cout << p[0] << " + ";
					for (int i = 1; i < N - 1; ++i)
						cout << p[i] << "*x^" << i << " + ";
					cout << p[N - 1] << "*x^" << N - 1 << endl << endl;

					//Убеждаемся в том, что результат точный (погрешность нулевая)
					cout << "Точное значение интеграла от многочлена: " << I_p << endl;
					cout << "Значение интеграла, вычисленное по ИКФ = " << J_p << endl;
					cout << "Фактическая погрешность: " << fabs(J_p - I_p) << endl << endl;
					system("pause");
				}

				//точное значение интеграла от функции sin(x) (по СКФ средних прямоугольников)
				long double I = CQF_for_func(a, b, f);
				cout << endl << "Точное значение интеграла от функции sin(x): " << I << endl;

				//приближенное значение интеграла (интеграл от функции по ИКФ)
				long double J = 0;
				for (int i = 0; i < N; ++i)
					J += A[i] * f(x[i]);

				cout << "Значение интеграла, вычисленное по ИКФ:      " << J << endl;
				cout << "Фактическая погрешность: " << fabs(J - I) << endl << endl;
				system("pause");

				//КФ НАСТ
				cout << endl << "---------------------------------------------------------------------------------------" << endl;
				cout << "Приближенное вычисление интеграла с помощью КФНАСТ." << endl;
				cout << "---------------------------------------------------------------------------------------" << endl;

				//инициализация матрицы системы
				for (int i = 0; i < N; ++i)
				{
					for (int j = 0; j < N; ++j)
					{
						c[i][j] = m[i + j];
					}
					c[i][N] = -m[i + N];
				}

				//решение системы
				long double* aa = new long double[N + 1];
				aa = Gauss_method(c, N);
				aa[N] = 1;

				//вывод ортогонального многочлена
				cout << endl << "Найденный ортогональный многочлен:" << endl;
				cout << "w(x) = ";
				cout << setprecision(3) << fixed;
				cout << aa[0] << ' ';
				for (int i = 1; i < N; ++i)
					cout << showpos << aa[i] << "x^" << noshowpos << i << ' ';//чтобы выводил "+"
				cout << "+ x^" << N << endl;

				//решение уравнения W = 0 для нахождения узлов интерполяции
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
						//отделение корней
						int M = 10000;
						int counter = 0;
						long double h = (b - a) / M;
						long double x1 = a;
						long double x2 = a + h;
						long double y1 = polinom(N + 1, aa, x1);//ортогональный многочлен
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

						//метод секущих
						cout << endl << "Найденные узлы:" << endl << endl;
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

				//инициализация системы для нахождения коэффициентов A_к
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
				//решение системы
				A = Gauss_method(c, N);

				cout << endl << "Найденные коэффициенты КФ НАСТ: " << endl << endl;
				for (int i = 0; i < N; ++i)
					cout << "A[" << i << "] = " << A[i] << endl;

				//Проверка на одночлене степени 2N-1
				cout << endl << "Если хотите сделать проверку формулы на одночлене, введите 1 (иначе - 0). " << endl;
				cin >> flag;
				if (flag)
				{
					long double J_p = 0;//значение, вычисленное по КФ НАСТ на одночлене степени 2N-1
					long double tmp = 1;//в будущем это х в степени 2N-1
					for (int i = 0; i < N; ++i)
					{
						tmp = 1;
						for (int j = 0; j < 2 * N - 1; ++j)//возведение х в степень 2N-1
							tmp *= x[i];
						J_p += tmp * A[i];
					}

					cout << endl << "f(x) = x^" << 2 * N - 1 << endl << endl;
					cout << "Точное значение интеграла от одночлена: " << m[2 * N - 1] << endl;//кэффициент при старш степени =0
					cout << "Значение, вычисленное по КФ НАСТ:       " << J_p << endl;
					cout << "Фактическая погрешность: " << fabs(m[2 * N - 1] - J_p) << endl << endl;
					system("pause");

				}

				//посчитаем значение интеграла от функции sin(x)
				J = 0;
				for (int i = 0; i < N; ++i)
					J += A[i] * f(x[i]);

				cout << endl;
				cout << "Точное значение интеграла от функции sin(x): " << I << endl;
				cout << "Значение интеграла, вычисленное по КФ НАСТ:  " << J << endl;
				cout << "Фактическая погрешность: " << fabs(I - J) << endl;

				delete[] x;
				delete[] m;
				delete[] z;
				delete[] A;
				for (int i = 0; i < N; ++i)
					delete[] c[i];
				delete[] c;

				cout << endl << "Если хотите изменить параметры задачи, введите 1 (иначе - 0)." << endl;
				cin >> flag;

			} while (flag);
			break;
		};
		case 2:
		{
			cout << "Если хотите применить КФ Гаусса, введите 1 (иначе - 0)." << endl;
			cin >> flag;
			if (flag) {
				double a{ -1 }, b{ 1 };//для КФ Гаусса границы заданы, фиксированы
				int N;

				cout << endl << "ВЫЧИСЛЕНИЕ ИНТЕГРАЛОВ ПРИ ПОМОЩИ КФ ГАУССА." << endl << endl;
				cout << "      f(x) = cos(x^2),  ro(x) = 1 " << endl << endl;
				double** x = new double* [8];//содержит массивы, в которых содержатся узлы
				double** A = new double* [8];//содержит массивы, в которых содержатся коэффициенты
				for (int i = 0; i < 8; ++i) {
					x[i] = new double[8];//содержит узлы при конкретном количестве узлов (не все ячейки заполняются)
					A[i] = new double[8];//кодержит коэффициенты при заданном количестве узлов (не все ячейки заполняются)
				}

				//находим корни многочлена Лежандра
				for (int j = 0; j < 8; ++j) {

					cout << "-------------------------------------------------------------------------" << endl;
					cout << "                         N = " << j + 1 << endl;
					cout << "-------------------------------------------------------------------------" << endl;

					//отделение корней
					N = j + 1;
					int M = 10000;
					int counter = 0;
					double h = (b - a) / M;
					double x1 = a;
					double x2 = a + h;
					double y1 = P(N, x1);//многочлен Лежандра
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

					//метод секущих
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

					//находим коэффициенты
					for (int i = 0; i < N; ++i)
					{
						double tmp = P_der(N, x[j][i]);
						A[j][i] = 2.0 / ((1 - x[j][i] * x[j][i]) * tmp * tmp);//поиск А_к (задание_5_теория, часть2, стр3)
					}

					//х_к симметрич относ 0, так как вес четный и отрезок симметричный
					//А_к при симметрич х_к равны, так как выражение для А_к четно относительно х_к 
					cout << endl << "Найденные узлы и коэффициенты:" << endl << endl;
					cout << setprecision(18) << scientific;
					for (int i = 0; i < N; ++i)
					{
						if (i > 9)
							cout << "x[" << i << "] = " << setw(24) << x[j][i] << "     " << "A[" << i << "] = " << setw(24) << A[j][i] << endl;
						else
							cout << "x[" << i << "] = " << setw(25) << x[j][i] << "     " << "A[" << i << "] = " << setw(25) << A[j][i] << endl;
					}

					cout << endl << "Проверка на многочлене степени " << 2 * N - 1 << ':' << endl;
					srand(time(0));
					int* p = new int[2 * N];
					for (int i = 0; i < 2 * N; ++i)
						p[i] = rand() % 101 - 50;

					//значение по КФ Гаусса
					double J_p = 0;
					for (int i = 0; i < N; ++i)
						J_p += A[j][i] * polinom(2 * N, p, x[j][i]);

					//точное значение (интегрируем многочлен)
					double I_p = 0;
					double aa = a;
					double bb = b;
					for (int i = 0; i < 2 * N; ++i)
					{
						I_p += (double)p[i] / (i + 1) * (bb - aa);
						aa *= a;
						bb *= b;
					}

					//выводим многочлен, на котором тестируем КФ Гаусса
					cout << endl << "f(x) = ";
					cout << p[0] << ' ';
					for (int i = 1; i < 2 * N - 1; ++i)
						cout << showpos << p[i] << "x^" << noshowpos << i << ' ';
					cout << showpos << p[2 * N - 1] << "x^" << noshowpos << 2 * N - 1 << endl << endl;

					cout << "Точное значение интеграла от многочлена: " << I_p << endl;
					cout << "Значение интеграла, вычисленное по ИКФ = " << J_p << endl;
					cout << "Фактическая погрешность: " << fabs(J_p - I_p) << endl << endl;
					system("pause");

				}

				//В подобной КФ Гаусса отрезок м.б. любым, не только [-1,1]
				cout << "Если хотите определить узлы и коэффициенты КФ, подобной КФ Гаусса, для N = 3, 6, 7, 8, введите 1 (иначе - 0)." << endl;
				cin >> flag;
				if (flag)
					do {
						double c, d;
						cout << endl << "Введите концы отрезка: " << endl;
						cin >> c >> d;

						int k[4]{ 2,5,6,7 };
						for (int j = 0; j < 4; ++j)
						{
							cout << "------------------------------------------------------------------" << endl;
							cout << "                 N = " << k[j] + 1 << endl;
							cout << "------------------------------------------------------------------" << endl;

							N = k[j] + 1;
							double* C = new double[N];//массив коэффициентов для подобной КФ Гаусса
							double* t = new double[N];//5.2 белая доска
							////if (c != -1 || d != 1)
							//{
							for (int i = 0; i < N; ++i) {
								C[i] = A[k[j]][i] * (d - c) / 2;//т и х перепутаны в "5.2_белая_доска"
								t[i] = (d - c) / 2 * x[k[j]][i] + (c + d) / 2;//С и А перепутаны в "5.2_белая_доска"
							}
							//}

							cout << endl << "Найденные узлы и коэффициенты КФ, подобной КФ Гаусса:" << endl << endl;
							cout << setprecision(18) << scientific;
							for (int i = 0; i < N; ++i)
								cout << "x[" << i << "] = " << setw(25) << t[i] << "     " << "A[" << i << "] = " << setw(25) << C[i] << endl;

							//значение, полученное с помощью подобной КФ Гаусса
							double J = 0;
							for (int i = 0; i < N; ++i)
								J += C[i] * func1(t[i]);

							cout << "Значение интеграла от функции cos(x^2) по отрезку [" << fixed << setprecision(2) << c << ", " << d << "]: " << setprecision(18) << J << endl;

							delete[] C;
							delete[] t;
							system("pause");
						}
						cout << "Если хотите поменять концы отрезка, введите 1 (иначе - 0)." << endl;
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

			cout << "Если хотите применить КФ Мелера, введите 1 (иначе - 0)." << endl;
			cin >> flag;
			if (flag) {
				cout << "ВЫЧИСЛЕНИЕ ИНТЕГРАЛОВ ПРИ ПОМОЩИ КФ МЕЛЕРА." << endl << endl;
				cout << endl << "   f(x) = e^x * sin(x^2),   ro(x) = 1 / sqrt(1 - x^2)" << endl << endl;
				do {
					int N;
					int n[3];
					cout << "Введите три значения N, для которых необходимо найти значение интеграла по КФ Мелера: " << endl;
					for (int i = 0; i < 3; ++i)
						cin >> n[i];// вводим количество узлов при которых хотим найти значение интеграла по КФ Мелера
					double J[3]{ 0 };//значение интеграла при данных количествах узлов

					double pi = 4.0 * atan(1.0);
					for (int i = 0; i < 3; ++i)
					{
						cout << "------------------------------------------------------------------" << endl;
						cout << "                 N = " << n[i] << endl;
						cout << "------------------------------------------------------------------" << endl;

						N = n[i];
						double* x = new double[N + 1];
						double J_tmp = 0;

						cout << endl << "Узлы: " << endl;
						for (int j = 1; j < N + 1; ++j)
						{
							x[j] = cos((2 * (double)j - 1) / (2 * (double)N) * pi);//Задание_5_Теория_часть2
							J_tmp += func2(x[j]);//потом домножим на А_к = pi/n (вынесли за скобку)

							if (i > 9)//для красивого вывода
								cout << "x[" << j << "] = " << setw(24) << setprecision(18) << x[j] << endl;
							else
								cout << "x[" << j << "] = " << setw(25) << setprecision(18) << x[j] << endl;
						}
						cout << endl << "Коэффициент: " << (pi / N) << endl;
						J_tmp *= (pi / N);
						J[i] = J_tmp;
						//cout << "Полученное значение интеграла : " << J << endl << endl;
						delete[] x;
						system("pause");
					}
					cout << endl;
					cout << " Количество узлов | Полученное значение интеграла " << endl;
					cout << "---------------------------------------------------" << endl;
					for (int i = 0; i < 3; ++i)
						cout << setw(18) << n[i] << '|' << setw(30) << J[i] << endl;

					cout << endl << "Если хотите изменить N, введите 1 (иначе - 0)." << endl;
					cin >> flag;
				} while (flag);
			}
			break;
		};
		case 3:
		{
			cout << endl << "ПРИБЛИЖЁННОЕ ВЫЧИСЛЕНИЕ ИНТЕГРАЛА ПРИ ПОМОЩИ СОСТАВНОЙ КФ ГАУССА." << endl << endl;
			cout << "      f(x) = sin(x),     ro(x) = e^x" << endl << endl;
			double a{ -1 }, b{ 1 };
			double arr_c[20]{ 0 };//массив начал отрезка
			double arr_d[20]{ 0 };//массив концов отрезка
			int number_of_nodes[20]{ 0 };//массив количества узлов
			int number_of_division_gaps[20]{ 0 };//массив промежутков деления
			double J[20]{ 0 };//массив значений интеграла
			int k = 0;//счетчик итераций (если будем пересчитывать при других входных данных, то у нас сохранятся предыдущие значения)

			do {
				++k;

				double c, d;
				cout << "Введите пределы интегрирования: " << endl;
				cin >> c >> d;
				arr_c[k - 1] = c;
				arr_d[k - 1] = d;

				int N;
				cout << "Введите число узлов: " << endl;
				cin >> N;
				number_of_nodes[k - 1] = N;

				int m;
				cout << "Введите число промежутков деления отрезка интегрирования: " << endl;
				cin >> m;
				number_of_division_gaps[k - 1] = m;

				double h = (d - c) / m;//шаг
				double* z = new double[m + 1];//массив узлов
				for (int i = 0; i < m + 1; ++i)
					z[i] = c + h * i;

				//находим коэффициенты для отрезка [-1,1]
				int M = 10000;
				int counter = 0;
				double delta = (b - a) / M;
				double x1 = a;
				double x2 = a + delta;
				double y1 = P(N, x1);
				double y2;
				double begin[100]{ 0 }, end[100]{ 0 };

				//находим отрезки перемены знака все еще для отрезка [-1,1]

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
				//метод секущих для уточнения корней все еще для отрезка [-1,1]

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
					x[i] = x2;//находим узлы все еще для отрезка [-1,1]
				}

				//вычисляем коэффициенты с помощью многочлена Лежандра все еще для отрезка [-1,1]
				double* A = new double[N];
				for (int i = 0; i < N; ++i)
				{
					double tmp = P_der(N, x[i]);
					A[i] = 2.0 / ((1 - x[i] * x[i]) * tmp * tmp);
				}

				//вывод узлов и коэффициентов для отрезка [-1,1]
				cout << endl << "Найденные узлы и коэффициенты:" << endl << endl;
				cout << setprecision(18) << scientific;
				for (int i = 0; i < N; ++i)//симметричны икс и аитые
				{
					if (i > 9)
						cout << "x[" << i << "] = " << setw(24) << x[i] << "     " << "A[" << i << "] = " << setw(24) << A[i] << endl;
					else
						cout << "x[" << i << "] = " << setw(25) << x[i] << "     " << "A[" << i << "] = " << setw(25) << A[i] << endl;
				}

				double new_J = 0;//в будущем - значение масштабированного интеграла на отрезке длиной h
				double* t = new double[N];//массив масштабированных узлов
				double tmp;
				for (int i = 0; i < m; ++i)//суммируем значения m интегралов
				{
					tmp = (z[i] + z[i + 1]) / 2.0;//5.3 белая доска
					for (int j = 0; j < N; ++j)
					{
						t[j] = h / 2.0 * x[j] + tmp;
						new_J += (h / 2.0) * A[j] * ro(t[j]) * f(t[j]);//phi=ro*f
					}
				}
				//new_J *= (h / 2.0);
				J[k - 1] = new_J;

				cout << endl << "     Отрезок      |     N     |     m     |        Значение интеграла       " << endl;
				cout << "-----------------------------------------------------------------------------------" << endl;
				for (int i = 0; i < k; ++i)
					cout << " [" << setw(6) << fixed << setprecision(2) << arr_c[i] << "," << setw(6) << arr_d[i] << "]  |" << setw(10) << number_of_nodes[i] << " |" << setw(10) << number_of_division_gaps[i] << " |" << setw(25) << setprecision(17) << J[i] << endl;

				delete[] z;
				delete[] x;
				delete[] t;
				delete[] A;

				cout << endl << "Если хотите изменить параметры задачи, введите 1 (иначе - 0)." << endl;
				cin >> flag;
			} while (flag && k < 20);
			break;
		};

		default:
			cout << "Некорректный ввод! Введите число от 1 до 3." << endl;
		}

		cout << "Введите номер задачи." << endl;
		cout << "1. Приближённое вычисление интеграла при помощью ИКФ НАСТ." << endl;
		cout << "2. Приближённое вычисление интеграла при помощи КФ Гаусса и Мелера." << endl;
		cout << "3. Приближённое вычисление интеграла при помощи составной КФ Гаусса." << endl;
		cout << "Если хотите завершить работу программы, введите 0." << endl;
		cin >> flag;

	} while (flag);

	return EXIT_SUCCESS;
}