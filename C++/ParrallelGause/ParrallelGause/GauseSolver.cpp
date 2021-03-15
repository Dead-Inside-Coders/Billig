#include <iostream>
#include <chrono>
#include <cmath>
#include "omp.h"
#include <thread>
#include <io.h>



class GauseSolver {

public:

	bool solve(float* M, int length, int rowCount)
	{

		// pivoting
		for (int col = 0; col + 1 < rowCount; col++)
		{
			if (M[col, col] == 0)
			{
				// find non-zero coefficient
				int swapRow = col + 1;
				for (; swapRow < rowCount; swapRow++) if (M[swapRow, col] != 0) break;

				if (M[swapRow, col] != 0) // found a non-zero coefficient?
				{
					// yes, then swap it with the above
					float* tmp = new float[rowCount + 1];
					for (int i = 0; i < rowCount + 1; i++)
					{
						tmp[i] = M[swapRow, i];
						M[swapRow, i] = M[col, i];
						M[col, i] = tmp[i];
					}
				}
				else return false; // no, then the matrix has no unique solution
			}
		}
		// elimination
#pragma omp parallel
		{

			for (int sourceRow = 0; sourceRow + 1 < rowCount; sourceRow++)
			{
#pragma omp for
				for (int destRow = sourceRow + 1; destRow < rowCount; destRow++)
				{
					float df = M[sourceRow, sourceRow];
					float sf = M[destRow, sourceRow];
					for (int i = 0; i < rowCount + 1; i++)
						M[destRow, i] = M[destRow, i] * df - M[sourceRow, i] * sf;
				}
			}
		}

		// back-insertion
		for (int row = rowCount - 1; row >= 0; row--)
		{
			float f = M[row, row];
			if (f == 0) return false;

			for (int i = 0; i < rowCount + 1; i++) M[row, i] /= f;
#pragma omp parallel 
			{
#pragma omp for
				for (int destRow = 0; destRow < row; destRow++)
				{
					M[destRow, rowCount] -= M[destRow, row] * M[row, rowCount];
					M[destRow, row] = 0;
				}
			}
		}
		return true;
	}

};