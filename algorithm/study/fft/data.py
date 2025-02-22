from math import *

def get_data(T, Fs):

    # make data
    x = []
    y = [2,3,1,0,0,0,0, 0]

    # for i in range(T*Fs):
    #     x.append(i/Fs)
    # for i in x:
    #     y.append(0.7*sin(2*pi*10*i) + sin(2*pi*150 * i) + sin(2*pi * 50 * i))

    return (x, y)

def preprocess_data(data, T, Fs):
    x, y  =data
    # make data to radix 2
    sample_capacity = int(pow(2, ceil(log2(T*Fs))))
    added_data = [0] * (sample_capacity - len(x))
    
    x = x + added_data.copy()
    y = y + added_data.copy()

    # to avoid y move, make avg to 0.
    # avg_y = sum(y)/len(y)
    # for i in range(len(y)):
    #     y[i] = y[i] - avg_y

    return x, y

