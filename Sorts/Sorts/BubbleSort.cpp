
#include <iostream>
#include "omp.h"

class BubbleSort
{
public:
	void sort(double* arr, int segmentCount, int length) {

#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < segmentCount; i++)
			{
				segmentSort(arr, segmentCount, i, length);
			}
		}
		for (int i = 0; i < length; i++)
		{
			printf("%.0f\n", arr[i]);
		}
		merge(arr, segmentCount, length);
	}

private:
	void segmentSort(double* arr, int segmentCount, int segment, int length) {

		int segmentLength = length - segment - 1;
		int m = segmentLength / segmentCount;
		double temp = 0;
		for (int k = 0; k < m; k++)
		{
			for (int i = segmentLength; i - segmentCount >= k * segmentCount; i = i - segmentCount)
			{
				if (arr[i] < arr[i - segmentCount])
				{
					temp = arr[i];
					arr[i] = arr[i - segmentCount];
					arr[i - segmentCount] = temp;
				}
			}
		}
	}
	void merge(double* arr, int segmentCount, int length) {

		int index_min = 0;
		double min = 0;
		int i = 0;
		double* tempArray = new double[length];
		int* start = new int[segmentCount];
		int* finish = new int[segmentCount];
		for (i = 1; i <= segmentCount; i++)
		{
			finish[segmentCount - i] = length - i;
			start[segmentCount - i] = finish[segmentCount - i] % segmentCount;
		}
		for (int k = 0; k < length; k++)
		{
			i = 0;
			while (start[i] > finish[i]) i++;
			index_min = i; min = arr[start[i]];
			for (int j = i + 1; j < segmentCount; j++)
			{
				if (start[j] <= finish[j])
				{
					if (arr[start[j]] < min)
					{
						min = arr[start[j]];
						index_min = j;
					}
				}
			}
			tempArray[k] = arr[start[index_min]];
			start[index_min] += segmentCount;
		}

		for (i = 0; i < length; i++)
			arr[i] = tempArray[i];
	}

};
