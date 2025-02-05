from math import *
from matplotlib import pyplot as plt
from data import *
from fft import *

# initialize
t = 2
Fs = 1000000

x, y = preprocess_data(get_data(t, Fs), t, Fs)

print('''
=======================
 ______ ______ _______ 
|  ____|  ____|__   __|
| |__  | |__     | |   
|  __| |  __|    | |   
| |    | |       | |   
|_|    |_|       |_|   
=======================
      ''')
print("Please, write the number if you want to see graph")
print("1. show graph")
print("2. skip showing graph")
is_show_graph = int(input('> ')) == 1

# show how the data looks
if(is_show_graph):
    plt.plot(x, y)
    plt.title("data")
    plt.show()


# do fft
print()
print("== fft start ==")
result = fft(y)
print("=== fft end ===")

# show the fft result
f_list = []
fft_result = []

print()
print("----------------------------------------------------------------------------")
print("| %-15s\t | %-15s\t\t | %-15s |" % ('f', 'value', 'lambda'))
print("----------------------------------------------------------------------------")
for i in range(len(result)):
    m = result[i]
    value = abs(m)/len(y)
    f = i*Fs/len(y)

    # value of fft is similar with T * Fs / 2 if the f is match.
    if(value > 0.3):
        print("| %15.10f\t | %15.10f\t\t | %15.10f |"%(f, value, 1/f if(f != 0) else inf))

    # for final fft result
    f_list.append(f)
    fft_result.append(value)
print("----------------------------------------------------------------------------")


if(is_show_graph):
    plt.plot(f_list, fft_result)
    plt.title("fft result")
    plt.show()
