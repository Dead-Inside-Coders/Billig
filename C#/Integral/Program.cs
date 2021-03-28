using System;
using System.Diagnostics;
using System.Threading.Tasks;

namespace Integral
{
    class Program
    {

        static double F(double x)
        {
            return 4 / (1 + Math.Pow(x, 2)); // Math.Pow(x, 2) * Math.Sin(x);
        }

        static double definiteIntegralT(double start, double finish, double eps)
        {

            int n = 1;
            double dx0 = (finish - start);
            double dx = dx0;
            double Sum0 = (F(start) + F(finish)) / 2;
            double S0 = Sum0 * dx0;
            double Sum1 = Sum0;
            double S1 = S0;
            double x0 = finish;
            double x = x0;

            while (true)
            {
                dx = dx / 2;
                Sum1 = 0;
                x0 = start + dx;
                for (int k = 0; k < n; k++)
                {
                    x = x0 + k * dx0;
                    Sum1 += F(x);
                }
                Sum1 += Sum0;
                S1 = Sum1 * dx;
                dx0 = dx;
                n *= 2;
                if (Math.Abs(S1 - S0) > eps)
                {

                    Sum0 = Sum1;
                    S0 = S1;
                }
                else
                    break;
            }
            return S1;
        }



        static double Integral(double a, double b, double eps, int p)
        {

            double[] result = new double[p];

           // ParallelOptions cc = new ParallelOptions();
            //cc.MaxDegreeOfParallelism = 1;
            //System.Threading.ThreadPool.SetMaxThreads(1,1);
            Parallel.For(0, p  ,(i) =>
            {
                double dx = (b - a) / p;
                double start = 0, finish = 0;
                start = a + i * dx;
                finish = start + dx;
                result[i] = definiteIntegralT(start, finish, eps);
            }); ;

            double finalResult = 0;

            for (int i = 0; i < p; i++)
            {
                finalResult += result[i];
            }
            return finalResult;
        }



        static void Main(string[] args)
        {
            Stopwatch stopwatch = Stopwatch.StartNew();
            //DateTime start, finish;
            //start = DateTime.Now;
            stopwatch.Start();
             Console.WriteLine("Result " + Integral(0, 1, 1e-16, 200));
            //finish = DateTime.Now;
            stopwatch.Stop();
            Console.WriteLine("Time " + stopwatch.ElapsedMilliseconds );//((finish - start).Ticks * 1e-8));//.Duration().Milliseconds));
        }
    }
}
