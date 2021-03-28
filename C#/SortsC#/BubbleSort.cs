using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Sorts
{
    class BubbleSort
    {
        public void sort(double[] arr, int segmentCount)
        {
            //ParallelOptions p = new ParallelOptions();
            //p.MaxDegreeOfParallelism = 5;
            Parallel.For(0, segmentCount ,(i) =>
            {
                segmentSort(arr, segmentCount, i);
            });
            merge(arr, segmentCount);
        }


        private void segmentSort(double[] arr, int segmentCount, int segment)
        {

            int segmentLength = arr.Length - segment - 1;
            int m = segmentLength / segmentCount;
            double temp = 0;
            for (int k = 0; k < m; k++)
            {
                for (int i = segmentLength; i - segmentCount >= k * segmentCount; i = i - segmentCount)
                {
                    if (arr[i] < arr[i - segmentCount])
                    {
                        temp = arr[i];
                        arr[i] = arr[i - segmentCount];
                        arr[i - segmentCount] = temp;
                    }
                }
            }
        }
        private void merge(double[] arr, int segmentCount)
        {
            int index_min = 0;
            double min = 0;
            int i = 0;
            double[] tempArray = new double[arr.Length];
            int[] start = new int[segmentCount];
            int[] finish = new int[segmentCount];
            for (i = 1; i <= segmentCount; i++)
            {
                finish[segmentCount - i] = arr.Length - i;
                start[segmentCount - i] = finish[segmentCount - i] % segmentCount;
            }
            for (int k = 0; k < arr.Length; k++)
            {
                i = 0;
                while (start[i] > finish[i]) i++;
                index_min = i; min = arr[start[i]];
                for (int j = i + 1; j < segmentCount; j++)
                {
                    if (start[j] <= finish[j])
                    {
                        if (arr[start[j]] < min)
                        {
                            min = arr[start[j]];
                            index_min = j;
                        }
                    }
                }
                tempArray[k] = arr[start[index_min]];
                start[index_min] += segmentCount;
            }

            for (i = 0; i < arr.Length; i++)
                arr[i] = tempArray[i];
        }

    }
}
