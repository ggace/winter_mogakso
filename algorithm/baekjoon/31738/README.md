# 31738
- [문제페이지](https://boj.kr/31738)

## 1) 문제 설명
n과 m이 주어질때, $n! \mod m$ 결과를 출력하는 문제이다.

## 2) 문제 풀이
m이 n보다 작다면 항상 0이다.

m이 n보다 크다면, m이 $10^7$ 이기 때문에, 브루트포스를 돌리면된다.

## 3) 코드
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll fastpow(ll a, ll n, ll c){
    ll result=1;
    while(n){
        if(n&1){
            result *=a;
            if(result>=c) result%=c;
        }
        a*=a;
        if(a>=c) a%=c;
        n>>=1;
    }
    return result;
}

int main() {
    ll n, m; cin >> n >> m;

    if(n >= m) {
        cout << "0\n";
        return 0;
    }

    ll r = n / m;

    ll result = 1;
    for(int i = 1; i <= m; i++) {
        ll t = r;
        if(i <= n % m) {
            t++;
        }
        result *= fastpow(i % m, t, m);
        result %= m;
    }
    cout << result << "\n";

}
```