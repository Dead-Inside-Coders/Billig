#include <iostream>
#include "omp.h"

class QuickSort
{
public:
	void  quickSort(double* arr, int segmentCount, int arrayLength)
	{
		int n = arrayLength;
		int m = n / segmentCount;
		/*omp_set_num_threads(5);*/
#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < segmentCount; i++)
			{
				int start = i * m;
				int finish = i != segmentCount - 1 ? start + m - 1 : n - 1;
				qSort(arr, start, finish);
			}
		}
		merge(arr, segmentCount, arrayLength);
	}

	void pQuickSort(double* arr, int arrayLength, int deapnesLimit)
	{
		//omp_set_num_threads(1);
		pQSort(arr, 0, arrayLength - 1, deapnesLimit);
	}

private:
	/// –екурсивна€ верси€ быстрой сортировки
	void qSort(double* arr, int start, int finish) {
		if (finish - start > 0)
		{
			double cand = 0, temp = 0;
			int l = start, r = finish;
			cand = arr[(r + l) / 2];
			while (l <= r)
			{
				while (arr[l] < cand) l++;
				while (arr[r] > cand) r--;
				if (l <= r)
				{
					temp = arr[l];
					arr[l] = arr[r];
					arr[r] = temp;
					l++; r--;
				}
			}
			qSort(arr, start, r);
			qSort(arr, l, finish);
		}
	}
	/// –екурсивна€ параллельна€ верси€ быстрой сортировки
	void pQSort(double* arr, int start, int finish, int deapnesLimit) {
		//const int deapnesLimit = 100000;
		if (finish - start > 0)
		{
			double cand = 0, temp = 0;
			int l = start, r = finish;
			cand = arr[(r + l) / 2];
			while (l <= r)
			{
				while (arr[l] < cand) l++;
				while (arr[r] > cand) r--;
				if (l <= r)
				{
					temp = arr[l];
					arr[l] = arr[r];
					arr[r] = temp;
					l++; r--;
				}
			}
			
#pragma omp parallel sections
			{
#pragma omp section
				{
					if ((r - start) > deapnesLimit)
					{

						pQSort(arr, start, r, deapnesLimit);

					}
					else
					{
						qSort(arr, start, r);
					}
				}
#pragma omp section
				{
					if ((finish - l) > deapnesLimit)
					{
						{
							pQSort(arr, l, finish, deapnesLimit);
						}
					}
					else
					{
						qSort(arr, l, finish);
					}
				}
			}
		}
	}


	void merge(double* mas, int p, int length) {

		int m = length / p;
		int index_min = 0;
		double min = 0;
		int i = 0;
		double* tmas = new double[length];
		int* start = new int[p];
		int* finish = new int[p];
		for (i = 0; i < p; i++)
		{
			start[i] = i * m;
			finish[i] = i != p - 1 ? start[i] + m - 1 : length - 1;
		}
		for (int k = 0; k < length; k++)
		{
			i = 0;
			while (start[i] > finish[i]) i++;
			index_min = i; min = mas[start[i]];

			for (int j = i + 1; j < p; j++)
			{
				if (start[j] <= finish[j])
				{
					if (mas[start[j]] < min)
					{
						min = mas[start[j]];
						index_min = j;
					}
				}
			}
			tmas[k] = mas[start[index_min]];
			start[index_min]++;
		}

		for (i = 0; i < length; i++)
			mas[i] = tmas[i];

	}
};

