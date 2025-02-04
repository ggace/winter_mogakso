from math import *
import numpy as np
from calculate_matrix import *

max_T = np.array([])

def matrix_initialize(n):
    global max_T
    n = int(n)
    matrix = np.identity(n, dtype=np.complex_)
    for i in range(n):
        k = -pi * i / n
        matrix[i][i] = np.exp(1j * k)
    max_T = matrix

def T(n):
    global max_T
    c = len(max_T)//n
    return max_T[::c, ::c]

def C(n):
    n = int(n)
    digit = int(log2(n))
    matrix = []
    for i in range(n):
        binary = bin(i)[2::]
        binary = '0' * (digit-len(binary)) + binary
        binary = binary[::-1]
        matrix.append(int('0b'+binary, 2))
    return np.array(matrix)


def F(l):
    if(l <= 2):
        return np.array([
            [1,1],
            [1,-1]
        ])

    F_n_2 = F(l//2)
    T_n = T(l//2)

    t_n = np.dot(T_n, F_n_2)

    percent = 100 * l/len(max_T)
    print("fft process: %7.3f" % percent, end=" %\n")

    matrix = attach(merge(F_n_2, t_n),  merge(F_n_2, minus(t_n)))

    return matrix


