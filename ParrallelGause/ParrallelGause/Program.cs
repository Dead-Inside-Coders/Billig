using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ParrallelGause
{
    class Program
    {
        public static void Main(String[] args)
        {
            int equations_amount;
            Console.WriteLine("Введите количество уравнений:");
            equations_amount = int.Parse(Console.ReadLine());

            float[,] matrix = new float[equations_amount, equations_amount + 1];
            float[,] copyMatrix = new float[equations_amount, equations_amount + 1];
         
            // Заполняем матрицу коэффициентов и B
            for (int i = 0; i < equations_amount; i++)
            {
                for (int j = 0; j < equations_amount + 1; j++)
                {
                    float randomValue = new Random().Next(0, 100);
                    matrix[i, j] = randomValue;
                    copyMatrix[i, j] = randomValue;
                }
            }

            DateTime start = DateTime.Now;
            Gause.Solve(matrix);
            DateTime end = DateTime.Now;
            double time = (end - start).Ticks;
            Console.WriteLine(" Gause Time: " + time);

            DateTime start1 = DateTime.Now;
            ParallelGause.Solve(copyMatrix);
            DateTime end1 = DateTime.Now;
            double time1 = (end1 - start1).Ticks;
            Console.WriteLine(" Parallel Gause Time: " + time1);

            Console.ReadKey();
        }
    }
}
