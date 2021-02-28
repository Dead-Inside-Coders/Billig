using System;

namespace Sorts
{
    class Program
    {
        static void Main(string[] args)
        {
            double[] array = new double[100000];
            for (int i = 0; i < array.Length; i++)
            {
                array[i] = new Random().Next(-1000, 1000);
            }

            BubbleSort bubbleSort = new BubbleSort();
            QuicSort quicSort = new QuicSort();

            DateTime start = DateTime.Now;
            bubbleSort.sort(array, 1);
            DateTime finish = DateTime.Now;
            double time = (finish - start).Ticks * 1e-7;

            Console.WriteLine("Время сортировки массива " + time);
        }
    }
}
