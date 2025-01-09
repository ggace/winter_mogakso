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
 - (2,1)
 - (1,2)
 - (2, -1)
 - (1, -2)

### 2. 표현
#### 위의 좌표를 통해 미지수 4개만을 사용해 나이트의 이동을 표현할 수 있으며 이를 행렬로 표현하면 다음과 같다.
$$
\begin{bmatrix}
2 & 1 &  2 &  1 \\
-1 & -2 & 1 & 2
\end{bmatrix} \times \begin{bmatrix}
a\\
b\\
c\\
d\\
\end{bmatrix} = \begin{bmatrix}
x\\
y
\end{bmatrix}
$$

### 3. 정수 a, b, c, d에 대한 식 찾기
$$
\begin{bmatrix}
2 & 1 &  2 &  1 \\
-1 & -2 & 1 & 2
\end{bmatrix} \times \begin{bmatrix}
a\\
b\\
c\\
d
\end{bmatrix} = \begin{bmatrix}
x\\
y
\end{bmatrix}
$$

$$
C = \begin{bmatrix}
2 & 1 &  2 &  1 \\
-1 & -2 & 1 & 2 
\end{bmatrix}, 
v = \begin{bmatrix}
a\\
b\\
c\\
d
\end{bmatrix}, 
B = \begin{bmatrix}
x\\
y\\
\end{bmatrix}
$$
$$
C \times v = B
$$
#### c와 d에 0을 대입해 특정한 x행렬을 얻을 수 있다.
$$
v_{specity} = \begin{bmatrix}
a\\
b\\
0\\
0
\end{bmatrix}
$$
$$
2a + b = x
$$
$$
-a - 2b = y
$$
$$
v_{specity} = \begin{bmatrix}
\frac{2x+y}{3} \\
-\frac{2y+x}{3}\\
0\\
0
\end{bmatrix}
$$

#### 이때, C $\times$ $v_{specity}$ = B이다. 
#### 만약 C $\times$ $v_{temp}$ = 0이라면 C $\times$ $(v_{specify} + v_{temp})$ = B이므로 $v_{temp}$를 찾아야한다.
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
\frac{2x+y}{3} \\
-\frac{2y-x}{3}\\
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
### 4. 결과
$$
R = |\frac{2x+y}{3} + \frac{5}{3} \lambda_1 + \frac{4}{3} \lambda_2 | + 
|-\frac{2y+x}{3} - \frac{4}{3} \lambda_1 - \frac{5}{3} \lambda_2 | + 
|\lambda_1| + 
|\lambda_2| 
$$
$$
= |\frac{2x+y}{3} + \frac{5}{3} \lambda_1 + \frac{4}{3} \lambda_2 | + 
|\frac{2y+x}{3} + \frac{4}{3} \lambda_1 + \frac{5}{3} \lambda_2 | + 
|\lambda_1| + 
|\lambda_2|
$$
#### 에서 R의 최솟값이 나이트 이동의 최소가 된다.
#### 이때, $\frac{5}{3}$과 $\frac{4}{3}$에 대해 정수 $\lambda_1$, $\lambda_2$가 주어진다면, 이때, 최솟값을 가지는 $\lambda_1$과 $\lambda_2$는 유일할 수 밖에 없기 때문에 공간에서 삼분탐색을 진행하여 최솟값을 찾을 수 있다.

#### $2x+y+5\lambda_1 + 4\lambda_2$와 $x+2y+4\lambda_1 + 5\lambda_2$가 모두 3의 배수여야 한다.
#### 이때, $\lambda_1 = 3n + t$, $\lambda_2 = 3m+k$라 하면

##### 1) $2x+y \equiv 0 (mod 3) (0 \le t \le 2)$
$$
R=|\frac{2x+y}{3} + 3t + 5n + 4m| + |\frac{x+2y}{3} + 3t + 4n + 5m| + |3n + t| + |3m + t|
$$
##### 2) $2x+y \equiv 1 (mod 3) (0 \le t \le 2)$
$$ 
R=|\frac{2x+y-4}{3} + 3t + 5n + 4m| + |\frac{x+2y-5}{3} + 3t + 4n + 5m| + |3n + t| + |3m + t-1|
$$
##### 3) $2x+y \equiv 2 (mod 3) (0 \le t \le 2)$
$$
R=|\frac{2x+y+4}{3} + 3t + 5n + 4m| + |\frac{x+2y+5}{3} + 3t + 4n + 5m| + |3n + t| + |3m + t+1|
$$

#### 이다. 따라서 해당 조건에 맞춰 t값을 0부터 2까지 조정하며 각각 삼분탐색을 통해 최솟값을 구해 최종 최솟값을 구해 답을 구할 수 있다. 

#### 이때, 각 테스트 케이스마다 걸리는 시간은 약 $3log_{1.5} (2 \times 10^9)$이다.