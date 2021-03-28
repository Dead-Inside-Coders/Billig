using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace Sorts
{
    class QuicSort
    {

        public void quickSort(double[] arr, int segmentCount)
        {
            //ParallelOptions p = new ParallelOptions();
            //p.MaxDegreeOfParallelism = 3;
            int n = arr.Length;
            int m = n / segmentCount;
            Parallel.For(0, segmentCount,(i) =>
            {
                int start = i * m;
                int finish = i != segmentCount - 1 ? start + m - 1 : n - 1;
                qSort(arr, start, finish);
            });
            merge(arr, segmentCount);
        }

        public void pQuickSort(double[] arr, int deapnesLimit)
        {
            pQSort(arr, 0, arr.Length - 1, deapnesLimit);
        }

        private void qSort(double[] arr, int start, int finish)
        {
            if (finish - start > 0)
            {
                double cand = 0, temp = 0;
                int l = start, r = finish;
                cand = arr[(r + l) / 2];
                while (l <= r)
                {
                    while (arr[l] < cand) l++;
                    while (arr[r] > cand) r--;
                    if (l <= r)
                    {
                        temp = arr[l];
                        arr[l] = arr[r];
                        arr[r] = temp;
                        l++; r--;
                    }
                }
                qSort(arr, start, r);
                qSort(arr, l, finish);
            }
        }
        /// Рекурсивная параллельная версия быстрой сортировки
        void pQSort(double[] arr, int start, int finish, int deapnesLimit)
        {
            if (finish - start > 0)
            {
                double cand = 0, temp = 0;
                int l = start, r = finish;
                cand = arr[(r + l) / 2];
                while (l <= r)
                {
                    while (arr[l] < cand) l++;
                    while (arr[r] > cand) r--;
                    if (l <= r)
                    {
                        temp = arr[l];
                        arr[l] = arr[r];
                        arr[r] = temp;
                        l++; r--;
                    }
                }
                bool p1, p2;
                p1 = (r - start) > deapnesLimit;
                p2 = (finish - l) > deapnesLimit;
                Task task1 = null, task2 = null;
                if (p1)
                {
                    task1 = new Task(() =>
                     {
                         pQSort(arr, start, r, deapnesLimit);
                     });
                    task1.Start();

                }
                else
                {
                    qSort(arr, start, r);
                }


                if (p2)
                {
                    task2 = new Task(() =>
                    {
                        pQSort(arr, l, finish, deapnesLimit);
                    });
                    task2.Start();
                }
                else
                {
                    qSort(arr, l, finish);
                }
                if (p1 && task1 != null) task1.Wait();
                if (p2 && task2 != null) task2.Wait();
            }
        }

        private void merge(double[] mas, int p)
        {
            int m = mas.Length / p;
            int index_min = 0;
            double min = 0;
            int i = 0;
            double[] tmas = new double[mas.Length];
            int[] start = new int[p];
            int[] finish = new int[p];
            for (i = 0; i < p; i++)
            {
                start[i] = i * m;
                finish[i] = i != p - 1 ? start[i] + m - 1 : mas.Length - 1;
            }
            for (int k = 0; k < mas.Length; k++)
            {
                i = 0;
                while (start[i] > finish[i]) i++;
                index_min = i; min = mas[start[i]];

                for (int j = i + 1; j < p; j++)
                {
                    if (start[j] <= finish[j])
                    {
                        if (mas[start[j]] < min)
                        {
                            min = mas[start[j]];
                            index_min = j;
                        }
                    }
                }
                tmas[k] = mas[start[index_min]];
                start[index_min]++;
            }

            for (i = 0; i < mas.Length; i++)
                mas[i] = tmas[i];

        }


    }
}
