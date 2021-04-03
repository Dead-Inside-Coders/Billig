def partition(array, begin, end):
    pivot_idx = begin
    for i in range(begin+1, end+1):
        if array[i] <= array[begin]:
            pivot_idx += 1
            array[i], array[pivot_idx] = array[pivot_idx], array[i]
    array[pivot_idx], array[begin] = array[begin], array[pivot_idx]
    return pivot_idx
def quick_sort_recursion(array, begin, end):
    if begin >= end:
        return
    pivot_idx = partition(array, begin, end)
    quick_sort_recursion(array, begin, pivot_idx-1)
    quick_sort_recursion(array, pivot_idx+1, end)

def quick_sort(array, begin=0, end=None):
    if end is None:
        end = len(array) - 1
   
    return quick_sort_recursion(array, begin, end)
def bubble_sort(arr):
    def swap(i, j):
        arr[i], arr[j] = arr[j], arr[i]
    n = len(arr)
    swapped = True
    x = -1
    while swapped:
        swapped = False
        x = x + 1
        for i in range(1, n-x):
            if arr[i - 1] > arr[i]:
                swap(i - 1, i)
                swapped = True
# Замер текущего времени (фиксация начала исполнения)
from concurrent import futures
from time import time, sleep
import random
start=time()
arr=[random.random() for i in range(10000)]
# Формирование пула процессов под управлением блока main
if __name__ == '__main__':
    # назначение задач процессам и планиравание их запуска
    with futures.ProcessPoolExecutor() as executor:
        todo = []
        future = executor.submit(bubble_sort(arr))
        # планирование запуска
        todo.append( future )
#        for future in futures.as_completed(todo):
            # вывод результатов по завершении процессов
#            print(future.result())
print(f"Программа выполнена в течение {time() - start} с.")
#print(arr)