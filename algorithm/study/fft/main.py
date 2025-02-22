from math import *
from matplotlib import pyplot as plt
from data import *
from fft import *

# initialize
t = 8
Fs = 1

x, y = preprocess_data(get_data(t, Fs), t, Fs)

# do fft
print()
result1 = fft([2,3,1,0,0,0,0,0])
result2 = fft([1,4,3,0,0,0,0,0])

# show the fft result
for i in range(len(result1)):
    m = result1[i] * result2[i]
    print(m)
