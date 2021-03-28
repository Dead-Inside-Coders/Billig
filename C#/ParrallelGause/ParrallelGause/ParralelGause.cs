using System;
using System.Threading.Tasks;

namespace ParrallelGause
{
    public static class ParallelGause
    {

        static void PrintMatrix(float[,] a, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j <= n; j++)
                    Console.Write(a[i, j] + " ");
                Console.WriteLine();
            }
        }

        /// <summary>Computes the solution of a linear equation system.</summary>
        /// <param name="M">
        /// The system of linear equations as an augmented matrix[row, col] where (rows + 1 == cols).
        /// It will contain the solution in "row canonical form" if the function returns "true".
        /// </param>
        /// <returns>Returns whether the matrix has a unique solution or not.</returns>
        public static bool Solve(float[,] M)
        {
            // input checks
            int rowCount = M.GetUpperBound(0) + 1;
            if (M == null || M.Length != rowCount * (rowCount + 1))
                throw new ArgumentException("The algorithm must be provided with a (n x n+1) matrix.");
            if (rowCount < 1)
                throw new ArgumentException("The matrix must at least have one row.");

            // pivoting
            for (int col = 0; col + 1 < rowCount; col++) if (M[col, col] == 0)
                // check for zero coefficients
                {
                    // find non-zero coefficient
                    int swapRow = col + 1;
                    for (; swapRow < rowCount; swapRow++) if (M[swapRow, col] != 0) break;

                    if (M[swapRow, col] != 0) // found a non-zero coefficient?
                    {
                        // yes, then swap it with the above
                        float[] tmp = new float[rowCount + 1];
                        for (int i = 0; i < rowCount + 1; i++)
                        {
                            tmp[i] = M[swapRow, i];
                            M[swapRow, i] = M[col, i];
                            M[col, i] = tmp[i];
                        }
                    }
                    else return false; // no, then the matrix has no unique solution
                }
            ParallelOptions op = new ParallelOptions();
            op.MaxDegreeOfParallelism = 5;
            // elimination
            //parallel for
            Parallel.For(0, rowCount - 1,op, (sourceRow) => {
                for (int destRow = sourceRow + 1; destRow < rowCount; destRow++)
                {
                    float df = M[sourceRow, sourceRow];
                    float sf = M[destRow, sourceRow];
                    for (int i = 0; i < rowCount + 1; i++)
                        M[destRow, i] = M[destRow, i] * df - M[sourceRow, i] * sf;
                }
            });
           
            // back-insertion
            for (int row = rowCount - 1; row >= 0; row--)
            {
                float f = M[row, row];
                if (f == 0) return false;

                for (int i = 0; i < rowCount + 1; i++) M[row, i] /= f;
                //parallel for
                Parallel.For(0, row, op, (destRow) => {
                    M[destRow, rowCount] -= M[destRow, row] * M[row, rowCount];
                    M[destRow, row] = 0;
                });
            }
            return true;
        }

        static float random(int min, int max)
        {
            if (min == max)
                return min;
            return min + new Random().Next() % (max - min);
        }
           
    }

}
