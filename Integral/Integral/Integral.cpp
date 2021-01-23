// Integral.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include <cmath>
#include "omp.h"
#include <thread>

inline double F(double x)
{
	return pow(x, 2) * sin(x); //cos(sin(x * x) - x * x * x + x * x * x * x / 47 - 54 * cos(pow(x, -1.5)));
}

int main()
{
	auto start_time = std::chrono::high_resolution_clock::now();

	const double begin = 1;// 1; //граници интегрирования 
	const double end = 10;//200; //граници интегрирования 
	const long int values_count = 1e7; //шаг 

	double* web = new double[values_count]; 
	web[0] = begin;

#pragma omp parallel
	{
#pragma omp for
		for (int i = 1; i < values_count - 1; ++i) {
			web[i] = begin + ((end - begin) / (values_count - 1)) * i;
		}
	}
	web[values_count - 1] = end;
	double res = 0;


	//omp_set_num_threads(5); // число потоков 
#pragma omp parallel
	{
		double a, b; //граници интегрирования 
		double prores = 0; //результат
#pragma omp for
		for (int i = 0; i < (values_count - 1); ++i)
		{
			a = web[i];
			b = web[i + 1];
			prores += (b - a) * ((F(a) + F(b)) / 2);
		}
#pragma omp atomic
		res += prores;
	}

	delete[] web;

	auto stop_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

	printf("Integral = %f\n", res);
	printf("Time spent: %d", duration.count());

}


