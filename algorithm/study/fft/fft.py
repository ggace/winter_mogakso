from math import *

def C(x):
    n = 1
    log_n = 0
    while(n < len(x)):
        n <<= 1
        log_n += 1
    
    matrix = []

    for i in range(n):
        temp = 0
        binary = 1
        reverse_binary = n >> 1
        for j in range(log_n):
            if(i & binary):
                temp |= reverse_binary
            reverse_binary >>= 1
            binary <<= 1
        matrix.append(x[temp])
    return matrix

def fft(x):
    C_m = C(x)
    size = len(C_m)
    
    i = 2
    while(True):
        
        if(i > size):
            break;
        
        print("%12.8f"%((size - size/i)/size * 100), end=" %\n")

        for t in range(size//i):
            
            for j in range(0, i//2):
                theta = -2*pi*j/i
                Wk = complex(cos(theta), sin(theta))
                front_index = j + i*t
                back_index = j + i//2+i*t
                front = C_m[front_index]
                back = C_m[back_index]

                C_m[front_index] = front + Wk * back
                C_m[back_index]  = front - Wk * back

                # print(f"{front_index} + {j}_{i} {back_index}")
                # print(f"{front_index} - {j}_{i} {back_index}")
                # print()
        i <<= 1

    return C_m