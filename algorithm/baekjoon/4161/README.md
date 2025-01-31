# 4161 풀이

## 1. 문제 
[백준](https://boj.kr/4616)
### - 문제 설명
#### 이 문제는 체스의 나이트가 움직여 갈 수 있는 위치가 주어지면 그 위치로 가는 최소 횟수를 각 줄에 표시하는 문제이다. 이는 x y 형태로 주어지며 나이트가 갈 수 있는 방향은 
 - (2,1)
 - (2, -1)
 - (1, 2)
 - (1,-2)
 - (-2, 1)
 - (-2, -1)
 - (-1, 2)
 - (-1, -2)
##### 이다. 

## 문제 풀이
### 1. 기본 발상
#### 문제에서 (2, 1)과 (-2, -1)는 +와 -관계로 표현할 수 있기 때문에 이처럼 나타낼 수 있는 방향을 중복을 없애 나타내면 다음과 같다.
 - (2,-1)
 - (1,-2)
 - (2, 1)
 - (1, 2)

### 2. 표현
#### 위의 좌표를 통해 미지수 4개만을 사용해 나이트의 이동을 표현할 수 있으며 이를 행렬로 표현하면 다음과 같다. (A, B, C, D는 미지수 4개 / a, b는 이동해야하는 위치)
$$
\begin{bmatrix}
2 & 1 &  2 &  1 \\
-1 & -2 & 1 & 2
\end{bmatrix} \times \begin{bmatrix}
A\\
B\\
C\\
D\\
\end{bmatrix} = \begin{bmatrix}
a\\
b
\end{bmatrix}
$$

### 3. 정수 a, b, c, d에 대한 식 찾기
$$
\begin{bmatrix}
2 & 1 &  2 &  1 \\
-1 & -2 & 1 & 2
\end{bmatrix} \times \begin{bmatrix}
A\\
B\\
C\\
D
\end{bmatrix} = \begin{bmatrix}
a\\
b
\end{bmatrix}
$$

$$
P = \begin{bmatrix}
2 & 1 &  2 &  1 \\
-1 & -2 & 1 & 2 
\end{bmatrix}, 
v = \begin{bmatrix}
A\\
B\\
C\\
D
\end{bmatrix}, 
Q = \begin{bmatrix}
a\\
b\\
\end{bmatrix}
$$
$$
P \times v = Q
$$
#### c와 d에 0을 대입해 특정한 x행렬을 얻을 수 있다.
$$
v_{specity} = \begin{bmatrix}
A\\
B\\
0\\
0
\end{bmatrix}
$$
$$
2A + B = a
$$
$$
-A - 2B = b
$$
$$
v_{specity} = \begin{bmatrix}
\frac{2a+b}{3} \\
-\frac{2b+a}{3}\\
0\\
0
\end{bmatrix}
$$

#### 이때, P $\times$ $v_{specity}$ = Q이다. 
#### 만약 P $\times$ $v_{temp}$ = 0이라면 C $\times$ $(v_{specify} + v_{temp})$ = B이므로 $v_{temp}$를 찾아야한다.
#### C의 3번째 열과 4번째 열은 C의 첫번째 열과 두번째열의 요소로 표현이 가능하기 때문에 
$$
v_{temp1} = \begin{bmatrix}
\frac{5}{3} \\
-\frac{4}{3}\\
-1\\
0\\
\end{bmatrix} \\
v_{temp2} = \begin{bmatrix} 
\frac{4}{3} \\
-\frac{5}{3}\\
0\\
-1\\
\end{bmatrix}
$$
#### 로 
$$
v 
= v_{specify} + \lambda_1 \times v_{temp1} + \lambda_2 \times v_{temp2}\\
= \begin{bmatrix}
\frac{2a+b}{3} \\
-\frac{2b+a}{3}\\
0\\
0\\
\end{bmatrix} + \lambda_1 \begin{bmatrix}
\frac{5}{3} \\
-\frac{4}{3}\\
-1\\
0\\
\end{bmatrix} + \lambda_2 \begin{bmatrix}
\frac{4}{3} \\
-\frac{5}{3}\\
0\\
-1\\
\end{bmatrix}
$$
#### 이다. 
$$
R 
= | \frac{2a+b}{3} + \frac{5}{3} \lambda_1 + \frac{4}{3} \lambda_2 | + | -\frac{2b+a}{3} - \frac{4}{3} \lambda_1 - \frac{5}{3} \lambda_2 | + | \lambda_1 | + | \lambda_2 | 
$$
$$
= | \frac{2a+b}{3} + \frac{5}{3} \lambda_1 + \frac{4}{3} \lambda_2 | + | \frac{2b+a}{3} + \frac{4}{3} \lambda_1 + \frac{5}{3} \lambda_2 | + | \lambda_1 | + | \lambda_2 |
$$
#### 이다. 

#### 이때, 
$$
\lambda_1 = 3n_1 + r_1 , \lambda_2 = 3n_2 + r_2 \\ 
= 3(n_1+y) + r_1 + t 
$$
$$
(n_2 = n_1 + y, r_2 = r_1+t)
$$
#### 이라 하자.

#### 이에 따라 아까 정리한 식을 정리하면, 
$$
result: | \frac{2a+b+4t}{3} + 3r_1 + 9n_1 + 4y | + | \frac{a+2b+5t}{3} + 3r_1 + 9n_1 + 5y | + | 3n_1 + r_1 | + | 3n_1 + r_1 + 3y + t |
$$
#### 이다. 

#### $3n_1 + r_1$은 어떠한 수도 될 수 있으며, 모든 부분에서 치환 가능하므로 $x = 3n_1 + r_1$이라 하자.

#### 이를 다시 정리하면, 
$$
| \frac{2a+b+4t}{3} + 3x + 4y | + | \frac{a+2b+5t}{3} + 3x + 5y | + | x | + | x + 3y + t |
$$
#### 이다. 

### 4. 교점
#### 각 절댓값 안의 식 간의 교점을 살펴보자.

$$
f(x) = \frac{2a+b+4t}{3} + 3x + 4y \\
g(x) = \frac{a+2b+5t}{3} + 3x + 5y \\
h(x) = x \\
i(x) = x + 3y + t
$$
#### 라 하자. 각 교점을 구하면,

$$ 
f(x) = g(x) \rightarrow ( \frac{b-2a}{3}, \frac{a-b-t}{3} ) \\
f(x) = h(x) \rightarrow (0, - \frac{2a+b+4t}{12} ) \\
f(x) = i(x) \rightarrow (- \frac{2a+b}{5}, \frac{2a+b-5t}{15} ) \\
g(x) = h(x) \rightarrow (0, - \frac{a+2b+5t}{15} ) \\
g(x) = i(x) \rightarrow (- \frac{a+2b}{4} , \frac{a+2b-5t}{12}) \\
h(x) = i(x) \rightarrow (0, -\frac{t}{3} )
$$
이다.

#### 이때, 함수 $f$~$i$의 기울기는 각각 $-\frac{3}{4}$, $-\frac{3}{5}$, $-\frac{1}{3}$이므로, 좌표의 $-2$ ~ $2$의 범위내에 최솟값이 있을것이라 생각했다. 

## 3. 코드
```c
typedef long long ll;

#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);

#include <bits/stdc++.h>

using namespace std;

ll f(ll a, ll b, ll x, ll y, ll t) {
    ll result = 0;
    result += abs((2*a + b + 4*t) / 3 + 3*x + 4*y);
    result += abs((a + 2*b + 5*t) / 3 + 3*x + 5*y);
    result += abs(x);
    result += abs(x + 3*y + t);

    return result;
}

void solution(ll a, ll b) {
    ll t = (a + 2*b) % 3;

    vector<array<ll, 2>> points = {
        {(b - 2*a)/3    ,  (a - b - t)/3},
        {0              , -(2*a + b + 4*t)/12},
        {-(2*a + b)/5   ,  (2*a + b - 5*t)/15},
        {0              , -(a + 2*b + 5*t)/15},
        {-(a + 2*b)/4   ,  (a + 2*b - 5*t)/12},
        {0              , -t/3}
    };

    ll result = LONG_LONG_MAX;

    for(int i = 0; i < 6; i++) {
        for(ll dx = -2; dx <= 2; dx++) {
            for(ll dy = -2; dy <= 2; dy++) {
                result = min(result, f(a, b, points[i][0] + dx, points[i][1] + dy, t));
            }
        }
    }
    cout << result << "\n";
}

int main(int argc, char* argv[]) {
    fio;

    while(true){

        string s;
        getline(cin, s); // 한 줄 입력받기

        if(s.compare("END") == 0) {
            break;
        }
        ll a, b;
        stringstream ss(s);
        ss >> a >> b;

        solution(a, b);
    }

    return 0;
}

```