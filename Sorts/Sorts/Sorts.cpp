// Sorts.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include <cmath>
#include "omp.h"
#include "BubbleSort.cpp"
#include "QuickSort.cpp"








int main()
{
    int arrayLength = 100000;
    double* arr = new double[arrayLength];
    for (int i = 0; i < arrayLength; i++)
    {
        arr[i] = rand();
       /* printf("%f\n", arr[i]);*/
    }
    
    BubbleSort bubbleSort;
    QuickSort quickSort;
    auto start_time = std::chrono::high_resolution_clock::now();
   // bubbleSort.sort(arr, 4, arrayLength);
    quickSort.quickSort(arr, 4, arrayLength);
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);
    printf("Time spent for sort sort: %d\n", duration.count());

    for (int i = 0; i < arrayLength; i++)
    {
       
         printf("%f\n", arr[i]);
    }
}
