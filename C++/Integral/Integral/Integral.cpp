// Integral.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include <cmath>
#include "omp.h"
#include <thread>
#include <io.h>

inline double F(double x)
{
	return 4 / (1 + pow(x, 2)); //pow(x,2)*sin(x)
}

double long definiteIntegralT(long double start, long double finish, long double eps) {

	int n = 1;
	double dx0 = (finish - start);
	double dx = dx0;
	double Sum0 = (F(start) + F(finish)) / 2;
	double S0 = Sum0 * dx0;
	double Sum1 = Sum0;
	double S1 = S0;
	double x0 = finish;
	double x = x0;

	while (true)
	{
		dx = dx / 2;
		Sum1 = 0;
		x0 = start + dx;
		for (int k = 0; k < n; k++)
		{
			x = x0 + k * dx0;
			Sum1 += F(x);
		}
		Sum1 += Sum0;
		S1 = Sum1 * dx;
		dx0 = dx;
		n *= 2;
		if (abs(S1 - S0) > eps)
		{

			Sum0 = Sum1;
			S0 = S1;
		}
		else
			break;
	}
	return S1;
}


double long Integral(long double a, long double b, long double eps, int p) {

	double* result = new double[p];
//omp_set_num_threads(5);
#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < p; i++)
		{
			double dx = (b - a) / p;
			double start = 0, finish = 0;
			start = a + i * dx;
			finish = start + dx;
			result[i] = definiteIntegralT(start, finish, eps);
		}
	}
	double long finalResult = 0;

	for (int i = 0; i < p; i++)
	{
		finalResult += result[i];
	}
	return finalResult;
}



int main()
{
	auto start_time = std::chrono::high_resolution_clock::now();
	//cout << Integral(0, 1, 1e-10, 100) << endl;
	/*for (size_t i = 0; i < 5; i++)
	{*/
		printf("Result %.15f\n", Integral(0, 1, 1e-15, 200));
	//}
	auto stop_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);
	printf("Time spent: %d\n", duration.count());

}


