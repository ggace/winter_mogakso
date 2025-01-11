# 32981 풀이

## 1. 문제 
[백준](https://boj.kr/32981)
### 1) 문제 설명

 이 문제는 찐 Even Number을 {0,2,4,6,8}로 이루어진 수라고 할때, 각 줄당 숫자의 자릿수가 주어지면 그 자릿수의 찐 Even Number을 출력하는 문제이다.

### 2) 문제 해설

이러한 문제는 고등학교 시절 경우의 수를 배우며 많이 접하게 되는 문제중 하나이다. {0,2,4,6,8}로만 이루어졌다고 하면, 자릿수가 1일경우 0,2,4,6,8로 총 5개, 자릿수가 2 이상일 경우
$$
\begin{pmatrix}
2\\ 4\\ 6\\ 8
\end{pmatrix}\begin{pmatrix}
0\\ 2\\ 4\\ 6\\ 8
\end{pmatrix}\begin{pmatrix}
0\\ 2\\ 4\\ 6\\ 8
\end{pmatrix}\begin{pmatrix}
0\\ 2\\ 4\\ 6\\ 8
\end{pmatrix}....
$$
로 나타난다. 따라서 자릿수가 2 이상일 경우 입력된 숫자가 n이라면 그 결과는 
$$
4 \times 5^{n-1}
$$
이다. 

이때, n은 $10^7$이기 때문에 그대로 곱셈을 진행하면 시간초과가 뜨게 된다. 따라서 이를 위한 방법이 필요하다. 

### 3) 제곱을 위한 함수
```c
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
```

먼저 코드를 살펴보면 다음과 같다. 

예를 들어 $5^{11}$은 $5^1 \times 5^2 \times 5^8$ 으로 5의 제곱수에 2의 제곱 꼴로 변화가 가능하다. 따라서, 함수의 a가 5, n이 11일때, $(((5^2)^2)^2)^{....}$ 로 계속 이전 수의 제곱을 하여 5의 지수가 2의 제곱 꼴로 나타나도록 할 수 있다.

이때, n이 11이면, n을 이진수로 나타내 ```0b1011```로, 각 진수가 1일경우에만 result값에 곱해 a의 n승을 구할수 있게 된다. 

이때, 모듈러는 다음과 같은 성질을 만족한다.
$$
(a+b) mod c \equiv (a mod c + b mod c) mod c \\
(a*b) mod c \equiv (a mod c \times b mod c) mod c
$$

따라서 매 곱셈마다 $mod c$ 를 통해 64번의 반복 연산만으로 a^n(mod c) 를 구할 수 있게 된다.

### 4) 코드
```c
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define println(s) cout << s << "\n"
#define mp() make_pair()
#define PRIME_SIZE 5
#define PIE M_PIf64

#ifdef BOJ
#define debug(x)  ((void)0);
#define debug_value(x)  ((void)0);
#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);
#else
#define debug(x)  cout << "[Debug] " << x;
#define debug_value(x)  cout << "[Debug] " << #x << " is " << x << '\n';
#define fio ((void)0);
#endif

#include <bits/stdc++.h>

using namespace std;

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

int main(int argc, char* argv[]) {
    fio; 

    int t;
    cin >> t;

    while(t--) {
        ll result = 1;

        ll x;
        cin >> x;

        if(x == 1) {
            cout << "5\n";
            continue;
        }

        result = fastpow(5, x-1, 1000000007);
        result *= 4;
        result %= 1000000007;

        cout << result << "\n";
    }

    return 0;
}
```