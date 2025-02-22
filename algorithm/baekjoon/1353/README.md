# 1353
- [문제페이지](https://boj.kr/1353)

## 1) 문제 설명
S와 P가 주어질때, 합이 S이고 곱이 P인 수열을 만들려고 할 때, 이 수열의 개수를 출력하면 된다.

## 2) 문제 풀이
$P = (\frac{S}{l})^l$ 인 $l$을 구해야 한다. 이때, 함수는 $e^{\frac{S}{e}}$ 보다 P가 크다면 불가능 하며, 나머지는 이진 탐색을 통해 구할 수 있다.

## 3) 코드
```cpp
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define PRIME_SIZE 5
#define PIE M_PIf64
#define E M_E
#define ln(x) log(x)

#ifdef BOJ
#define debug(x)  ((void)0);
#define debug_value(x)  ((void)0);
#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);
#else
#define debug(x)  cout << "[Debug] " << x << "\n";
#define debug_value(x)  cout << "[Debug] " << #x << " is " << x << '\n';
#define fio ((void)0);
#endif

#define inf (1e10)

#include <bits/stdc++.h>

using namespace std;

ll S, P;

long double func(long double l) {
    errno = 0;
    ld result = pow(S/l, l);
    return errno == ERANGE || fetestexcept(FE_OVERFLOW)? inf : result;
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> S >> P;
    if(S == P) {
        cout << "1\n";
        return 0;
    }

    ld possible_multiply = func((double)S/E);

    if(possible_multiply < P) {
        cout << "-1\n";
        return 0;
    }

    ll left = 2;
    ll right = (ll)(S/E) + 1;

    while(right - left > 1) {
        ll mid = (left + right)/2;

        ld r = func(mid);

        if(r < P) {
            left = mid;
        }
        else {
            right = mid;
        }
    }
    if(func(left) >= P) {
        cout << left << "\n";
    }
    else {
        cout << right << "\n";
    }

    return 0;
}

```