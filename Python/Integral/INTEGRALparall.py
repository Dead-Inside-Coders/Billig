def logtrapz(f, x, disable_checks=False, args=()):
    if isinstance(f, np.ndarray) or isinstance(f, list):
        if isinstance(x, np.ndarray) or isinstance(x, list):
            # check arrays are the same length
            if not disable_checks:
                assert len(f) == len(x) and len(x) > 1, "Function and function evaluation points are not the same length"

            if not disable_checks:
                # make sure x values are in ascending order (keeping f values associated to their x evaluation points)
                zp = np.array(sorted(zip(x, f)))

                # perform trapezium rule (internal logtrapzC function is faster than using scipy logsumexp)
                return logtrapzC(zp[:,1], zp[:,0])
            else:
                return logtrapzC(np.array(f), np.array(x))
        elif isinstance(x, float):
            assert x > 0., "Evaluation spacings must be positive"

            # perform trapezium rule
            return logtrapzC(f, np.array([x]))
        else:
            raise TypeError('Error... value of "x" must be a numpy array or a float')
    elif callable(f): # f is a function
        if isinstance(x, np.ndarray) or isinstance(x, list):
            if not disable_checks:
                assert len(x) > 1, "Function must be evaluated at more than one point"

            try:
                if not isinstance(args, tuple):
                    args = (args,)
                vs = f(np.array(x), args) # make sure x is an array when passed to function
            except Exception as e:
                raise RuntimeError('Error... could not evaluate function "f": {}'.format(e))

            if not disable_checks:
                # make sure x values are in ascending order (keeping f values associated to their x evaluation points)
                zp = np.array(sorted(zip(x, vs)))

                # perform trapezium rule (internal logtrapzC function is faster than using scipy logsumexp)
                return logtrapzC(zp[:,1], zp[:,0])
            else:
                return logtrapzC(vs, np.array(x))
        else:
            raise TypeError('Error... "x" must be a numpy array or list')
    else:
        raise RuntimeError('Error... "f" must be a numpy array, list, or callable function')
def integral(a, b, eps, q):
    k = 0.0
    for i in range(q):
        x = random.random()
        y = random.random()
        k += (x * x + y * y < 1.0)
    print(4 * k / q)    
    return(4 * k / q)
import numpy as np
from concurrent import futures
from time import time, sleep
import random
start=time()
# Формирование пула процессов под управлением блока main
if __name__ == '__main__':
    # назначение задач процессам и планиравание их запуска
    with futures.ProcessPoolExecutor() as executor:
        todo = []
        future = executor.submit(integral(0, 1, 1e-10, 100000000))
        # планирование запуска
        todo.append( future )
#        for future in futures.as_completed(todo):
            # вывод результатов по завершении процессов
#            print(future.result())
print(f"Программа выполнена в течение {time() - start} с.")
#print(arr)

