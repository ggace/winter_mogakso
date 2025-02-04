from math import *
import numpy as np
from calculate_matrix import *

def T(n):
    n = int(n)
    matrix = []
    for a in range(n):
        temp_matrix = []
        for b in range(n):
            if(a == b):
                k = -pi * a / (n)
                temp_matrix.append(np.exp(1j * k))
            else:
                temp_matrix.append(0)
        matrix.append(temp_matrix)
    return np.array(matrix)

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

    matrix = attach(merge(F_n_2, t_n),  merge(F_n_2, minus(t_n)))

    return matrix
    


