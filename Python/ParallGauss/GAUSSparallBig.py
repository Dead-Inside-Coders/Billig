def FancyPrint(A, B, selected):
    for row in range(len(B)):
       print("(", end='')
       for col in range(len(A[row])):
             print("\t{1:10.2f}{0}".format(" " if (selected is None
             or selected != (row, col)) else "*", A[row][col]), end='')
       print ("\t) * (\tX{0}) = (\t{1:10.2f})".format(row + 1, B[row]))
def SwapRows(A, B, row1, row2):
    A[row1], A[row2] = A[row2], A[row1]
    B[row1], B[row2] = B[row2], B[row1]
# --- конец перемены местами двух строк системы

# --- деление строки системы на число
def DivideRow(A, B, row, divider):
    A[row] = [a / divider for a in A[row]]
    B[row] /= divider
# --- конец деления строки системы на число

# --- сложение строки системы с другой строкой, умноженной на число
def CombineRows(A, B, row, source_row, weight):
    A[row] = [(a + k * weight) for a, k in zip(A[row], A[source_row])]
    B[row] += B[source_row] * weight
# --- конец сложения строки системы с другой строкой, умноженной на число

# --- решение системы методом Гаусса (приведением к треугольному виду)
def GaussO(A, B):
    column = 0
    while (column < len(B)):
        current_row = None
        for r in range(column, len(A)):
            if current_row is None or abs(A[r][column]) > abs(A[current_row][column]):
                 current_row = r
        if current_row is None:
           return "решений нет"
        FancyPrint(A, B, (current_row, column))
        if current_row != column:
            SwapRows(A, B, current_row, column)
            FancyPrint(A, B, (column, column))
        DivideRow(A, B, column, A[column][column])
        FancyPrint(A, B, (column, column))
        for r in range(column + 1, len(A)):
            CombineRows(A, B, r, column, -A[r][column])
        FancyPrint(A, B, (column, column))
        column += 1
        X = [0 for b in B]
        for i in range(len(B) - 1, -1, -1):
            X[i] = B[i] - sum(x * a for x, a in zip(X[(i + 1):], A[i][(i + 1):]))
    return X
#конец распраллеленного матода Гаусса   
from concurrent import futures
import random
from time import time, sleep
# Замер текущего времени (фиксация начала исполнения)
limit=150
A=[[random.randint(0,9) for i in range(limit)] for j in range((limit))]
B= [random.randint(0,9) for i in range(limit)]
#print(A)
#print(B)
start=time()
print("Распараллеленный процесс:")
# Формирвание пула процессов под управлением блока main
if __name__ == '__main__':
    # назначение задач процессам и планиравание их запуска
    with futures.ProcessPoolExecutor() as executor:
        todo = []
        future = executor.submit(GaussO,A,B)
        # планирование запуска
        todo.append( future )
        for future in futures.as_completed(todo):
            # вывод результатов по завершении процессов
            print(future.result())
print(f"Программа выполнена в течение {time() - start} с.")

