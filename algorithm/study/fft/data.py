import numpy as np
from math import *

def get_data(T, Fs):

    # make data
    x = np.arange(0, T, 1/Fs)
    y = [1, -1] * (len(x)//2)
    y = np.sin(1/2*pi*x)

    return (x, y)

def preprocess_data(data, T, Fs):
    x, y  =data
    # make data to radix 2
    sample_capacity = int(pow(2, ceil(log2(T*Fs))))
    added_count = sample_capacity - len(x)
    x = np.concatenate((x, np.zeros((sample_capacity - len(x)))), axis=0)
    y = np.concatenate((y, np.zeros((sample_capacity - len(y)))), axis=0)

    # to avoid y move, make avg to 0.
    avg_y = sum(y)/len(y)
    y = np.array(y) - avg_y

    return x, y

