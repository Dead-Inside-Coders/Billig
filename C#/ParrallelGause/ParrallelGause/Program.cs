using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ParrallelGause
{
    class Program
    {
        public static void Main(String[] args)
        {
            int equations_amount = 2000;

           // float[,] matrix = new float[equations_amount, equations_amount + 1];
            float[,] copyMatrix = new float[equations_amount, equations_amount + 1];
         
            // Заполняем матрицу коэффициентов и B
            for (int i = 0; i < equations_amount; i++)
            {
                for (int j = 0; j < equations_amount + 1; j++)
                {
                    float randomValue = i + j;//new Random().Next(0, 100);
                  //  matrix[i, j] = randomValue;
                    copyMatrix[i, j] = randomValue;
                }
            }

            //DateTime start = DateTime.Now;
            //Gause.Solve(matrix);
            //DateTime end = DateTime.Now;
            //double time = (end - start).Ticks;
            //Console.WriteLine(" Gause Time: " + time);

            Stopwatch stopwatch = Stopwatch.StartNew();
            stopwatch.Start();
            ParallelGause.Solve(copyMatrix); 
            stopwatch.Stop();
            double time1 = stopwatch.ElapsedMilliseconds; 
            Console.WriteLine(" Parallel Gause Time: " + time1);

            Console.ReadKey();
        }
    }
}
