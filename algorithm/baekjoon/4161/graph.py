import numpy as np
import matplotlib.pyplot as plt
import math
plt.rcParams['axes.unicode_minus'] = False

x = 1357
y = 7531

limit = 2
size = min(int(limit*2+1), 1000)

x_mov = 0
y_mov = -854

a, b = np.meshgrid(np.linspace(-limit + x_mov, limit+x_mov, size), np.linspace(-limit+y_mov, limit+y_mov, size))
t = (a+2*b) % 3

z = np.floor(abs((2*x + y + 4*t)/3 + 3*a + 4*b)).astype(int) + np.floor(abs((x + 2*y + 5*t)/3 + 3*a + 5*b)).astype(int) + np.floor(abs(a)).astype(int) + np.floor(abs(a + 3*b + t)).astype(int)

print(z)

fig = plt.figure(figsize=(12,8))
ax = fig.add_subplot()
contour1 = ax.contour(a, b, z, colors='k', linewidths=1, linestyles='--') ## 등고선
ax.clabel(contour1, contour1.levels, inline=True) ## contour 라벨

lvls = min(abs(size * 7) + abs(size*8) + abs(size) + abs(size*2), 256)

contour2 = ax.contourf(a, b, z, levels=lvls, cmap='Blues')
fig.colorbar(contour2) ## 컬러바 크기 축소 shrink

plt.show()