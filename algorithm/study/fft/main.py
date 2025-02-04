from math import *
from matrix import *
from calculate_matrix import *
from matplotlib import pyplot as plt
from graph import *
from data import *
from fft import *

# initialize
t = 24
Fs = 256

x, y = preprocess_data(get_data(t, Fs), t, Fs)

if(len(x) > 8192):
    print('\033[91m', end="")
    print("[Warning]")
    print('\033[37m', end="")
    print("  the size of data is too big. It may be killed by system.")
    print("  Will you keep running this program?")
    if(input("\033[93m  [Y/n] > \033[37m").lower() != 'y'):
        print("process end")
        exit(0)


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
print("====== fft start ======")
result = fft(y)
print("======= fft end ======")

# show the fft result
f_list = []
fft_result = []

print()
print("------------------------------------------------------------------------------------------------------------")
print("| %-15s\t | %-15s\t\t | %-22s \t | %-15s |" % ('f', 'value', 'real complex', 'lambda'))
print("------------------------------------------------------------------------------------------------------------")
for i in range(len(result)):
    m = result[i]
    value = np.abs(m[0])/len(y)
    f = i*Fs/len(y)

    # value of fft is similar with T * Fs / 2 if the f is match.
    if(value >0.2):
        print("| %15.10f\t | %15.10f\t\t | %10.5f+%10.5fi \t | %15.10f |"%(f, value, np.real(m[0]), np.imag(m[0]), 1/f if(f != 0) else inf))
        if(is_show_graph):
            drawGraphInComplex(t, Fs, i, y)

    # for final fft result
    f_list.append(f)
    fft_result.append(value)
print("------------------------------------------------------------------------------------------------------------")


if(is_show_graph):
    plt.plot(f_list, fft_result)
    plt.title("fft result")
    plt.show()
