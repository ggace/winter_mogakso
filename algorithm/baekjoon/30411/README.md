# 30411
- [문제페이지](https://boj.kr/30411)

## 1) 문제 설명
n과 k가 주어질때, 사이클상의 노드가 짝수 개만 존재하는 그래프를 만들어야한다.

## 2) 문제 풀이
$\sum_{i=1}^{n-1} \lfloor \frac{n-1-i}{2} \rfloor$ 으로 엣지 개수가 표현된다. 이를 만족한다면 이웃한 노드끼리 연결한 후 {1, 4}, {1, 6}, {1, 8}, {2, 5}, {2, 7}, ..... 이다. 이를 코드로 출력하기만 하면 된다.

## 3) 코드
```python
n, k = map(int, input().split())

possible = n-1
for i in range(1, n):
    possible += (n-1-i)//2
    if(possible >= k):
        print("YES")
        break

if(possible < k):
    print("NO")
    exit()
        

for i in range(1, n):
    print(f"{i} {i+1}")
    k -= 1
    if(k == 0):
        break;

for i in range(1, n):
    if(k == 0) :
        break;
    for j in range(i+3, n+1, 2):
        print(f"{i} {j}")
        k -= 1
        if(k == 0):
            break;

```