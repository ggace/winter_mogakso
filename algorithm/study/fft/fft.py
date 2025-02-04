import numpy as np
from matrix import *

def fft(x):
    front = F(len(x))

    r = []
    for i in C(len(x)):
        r.append([x[i]])
    r = np.array(r)
    return np.dot(front, r)