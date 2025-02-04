from matplotlib import pyplot as plt
import numpy as np
from math import *

def drawGraphInComplex(T, Fs, k, y):
    sample_capacity = int(pow(2, ceil(log2(T*Fs))))

    x = np.arange(0, T, 1/Fs)
    x = np.concatenate((x, np.zeros((sample_capacity - len(x)))), axis=0)

    c = np.exp(-2*pi * 1j * k * x / len(y)) * y

    a = np.real(c)
    b = np.imag(c)
    

    plt.scatter(a, b)
    plt.scatter([0], [0])
    plt.title(f"f: {k*Fs/sample_capacity}")
    plt.show()