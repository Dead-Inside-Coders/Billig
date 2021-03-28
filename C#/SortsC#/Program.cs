using System;
using System.Diagnostics;

namespace Sorts
{
    class Program
    {
        static void Main(string[] args)
        {
            double[] array = new double[1_000_000];
            Random a = new Random();
            for (int i = 0; i < array.Length; i++)
            {
                array[i] = a.Next(-1000, 1000);
            }
            BubbleSort bubbleSort = new BubbleSort();
            QuicSort quicSort = new QuicSort();
            Stopwatch stopwatch = Stopwatch.StartNew();
            
           // 
            stopwatch.Start();
            quicSort.pQuickSort(array, 1_000_000);
            stopwatch.Stop();
            Console.WriteLine("Time " + stopwatch.ElapsedMilliseconds);
        }
    }
}
