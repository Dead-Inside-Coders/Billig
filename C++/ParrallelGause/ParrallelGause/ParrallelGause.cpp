

#include <iostream>
#include <chrono>
#include "GauseSolver.cpp"



int main()
{

    int equations_amount = 2000;

    float* matrix = new float[equations_amount, equations_amount + 1];

    // Заполняем матрицу коэффициентов и B
    for (int i = 0; i < equations_amount; i++)
    {
        for (int j = 0; j < equations_amount + 1; j++)
        {
            float randomValue = i + j;
            matrix[i, j] = randomValue;
        }
    }
    GauseSolver gause;
    auto start_time = std::chrono::high_resolution_clock::now();
    gause.solve(matrix, equations_amount, equations_amount+1);
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);
    printf("Time spent for gause: %d\n", duration.count());

}

