# 15792
- [문제페이지](https://boj.kr/15792)

## 1) 문제 설명
A/B를 $10^{-1000}$ 범위까지 출력하는 문제이다.

## 2) 문제 풀이
컴퓨터에 맡기지 않고 실제 나누기 하듯 출력하면 된다.

## 3) 코드
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ll a, b; cin >> a >> b;

    cout << (int)(a / b) << ".";


    for(int i = 0; i < 1000; i++) {
        a %= b;
        a *= 10;
        cout << (int)(a/b);
    }
    cout << "\n";
}
```