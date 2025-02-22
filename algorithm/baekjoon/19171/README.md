# 19171
- [문제페이지](https://boj.kr/19171)

## 1) 문제 설명
페르마포인트를 3차원에서 구하는 문제이다. 

## 2) 문제 풀이
페르마 포인트는 다음과 같이 정의된다.

만약 삼각형의 가장 큰 각이 120도 이상이라면, 해당 각의 꼭짓점이 페르마 포인트가 된다.
만약 120도 미만이라면 $\sqrt{c^2 + a^2 - 2ac \cos({\theta + 60})}$ 이다. 

이때, 3차원 상에서도 a, b, c의 길이는 피타고라스 정리에 의해 계산 가능하고, theta 또한, 벡터 외적을 이용해 계산 가능하기 때문에 이를 토대로 계산하면 된다.

## 3) 코드
```python
from math import *

def is_pallarel(v1, v2):
    return v1[1] * v2[2] - v1[2] * v2[1] == 0 and v1[2] * v2[0] - v1[0] * v2[2] == 0 and v1[0] * v2[1] - v1[1] * v2[0] == 0

x1, y1, z1 = map(int, input().split());
x2, y2, z2 = map(int, input().split());
x3, y3, z3 = map(int, input().split());

v = [
    [
        (x2 - x1, y2 - y1, z2 - z1),
        (x3 - x1, y3 - y1, z3 - z1)
    ], 
    [
        (x3 - x2, y3 - y2, z3 - z2),
        (x1 - x2, y1 - y2, z1 - z2)
    ], 
    [
        (x1 - x3, y1 - y3, z1 - z3),
        (x2 - x3, y2 - y3, z2 - z3)
    ], 
]

d = [] # 2-1, 3-2, 1-3
for t in v:
    d_temp = 0;
    for i in range(3):
        d_temp += t[0][i] ** 2
    d.append(d_temp)

if is_pallarel(v[0][0], v[1][0]):
    x_min = min(x1, x2, x3)
    x_max = max(x1, x2, x3)
    y_min = min(y1, y2, y3)
    y_max = max(y1, y2, y3)
    z_min = min(z1, z2, z3)
    z_max = max(z1, z2, z3)
    print(sqrt((x_max - x_min) ** 2 + (y_max - y_min) ** 2 + (z_max - z_min) ** 2))
    exit(0)

dot = [] # 1 2 3

for t in v:
    dot_temp = 0
    for i in range(3):
        dot_temp += t[0][i] * t[1][i]
    dot.append(dot_temp)

angle_func = []

for i in range(3):
    cos_theta = dot[i] / (sqrt(d[i]) * sqrt(d[(i-1+3) % 3]))
    sin_theta = sqrt(1- cos_theta**2)
    if(degrees(acos(cos_theta)) >= 120):
        print(sqrt(d[i]) + sqrt(d[(i-1+3) % 3]))
        exit(0);
    angle_func.append((cos_theta, sin_theta))

l = sqrt(d[0] + d[2] - 2*sqrt(d[0])*sqrt(d[2])*(angle_func[0][0]/2 - angle_func[0][1]/2*sqrt(3)))

print(l)

```