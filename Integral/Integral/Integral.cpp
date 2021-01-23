// Integral.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include <cmath>
#include "omp.h"
#include <thread>

inline double F(double x)
{
	return cos(sin(x * x) - x * x * x + x * x * x * x / 47 - 54 * cos(pow(x, -1.5))); //pow(x,2)*sin(x)
}

long getIntegralResult(const double begin, const double end, const long steps) {

	auto start_time = std::chrono::high_resolution_clock::now();

	//const double begin = 1;// 1; //граници интегрирования 
	//const double end = 10;//200; //граници интегрирования 
	//const long values_count = 1e7; //шаг 

	double* web = new double[steps];
	web[0] = begin;

	//omp_set_num_threads(30); // число потоков

#pragma omp parallel
	{
#pragma omp for
		for (int i = 1; i < steps - 1; ++i) {
			web[i] = begin + ((end - begin) / (steps - 1)) * i;
		}
	}
	web[steps - 1] = end;
	double res = 0;


	 
#pragma omp parallel
	{
		double a, b; //граници интегрирования 
		double prores = 0; //результат
#pragma omp for
		for (int i = 0; i < (steps - 1); ++i)
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

	//printf("Integral = %f\n", res);
	//printf("Time spent: %d\n", duration.count());

	return duration.count();
}

int main()
{
	
	for (int i = 4; i < 9; i++)
	{
		long results = 0;
		for (int j = 0; j < 3; j++)
		{
			results += getIntegralResult(1, 10, pow(10,i));
		}
		printf("Avg time %d for epsilon 1e%d\n", results/2 ,i);
	}
	

}


