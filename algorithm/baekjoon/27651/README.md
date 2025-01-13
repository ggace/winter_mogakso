# 27651
- [문제 페이지](https://boj.kr/27651)

## 1) 문제 설명
n이 입력될 때, n 크기의 일차원 배열이 입력된다. 이를 a1, a2, ....., an이라 할때, 

$$
\sum_{i=1}^{X}{a_i} \le \sum_{i=Y+1}^{N}{a_i} \le \sum_{i=X+1}^{Y}{a_i} (1 \le X < Y < N)
$$
를 만족하는 (X, Y)쌍의 개수를 구하는 문제이다.

## 2) 문제 해설
먼저 1부터 i번째까지의 구간합을 head라 가정하자.

이때, body의 값은 $head + \frac{나머지}{2} < RESULT < 나머지 - head$ 일 것이다. 따라서 upper_bound($head + \frac{나머지}{2}$)와 lower_bound($나머지 - head$)의 차가 가능한 경우의 수가 된다.

## 3) 코드
```c
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define PRIME_SIZE 5
#define PIE M_PIf64

#ifdef BOJ
#define debug(x)  ((void)0);
#define debug_value(x)  ((void)0);
#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);
#else
#define debug(x)  cout << "[Debug] " << x << "\n";
#define debug_value(x)  cout << "[Debug] " << #x << " is " << x << '\n';
#define fio ((void)0);
#endif

#include <bits/stdc++.h>

using namespace std;

ll n;
vector<ll> v;
vector<ll> sums;

int main(int argc, char* argv[]) {
    fio; 

    cin >> n;
    v.resize(n+1);
    sums.resize(n+1);

    for(ll i = 1; i <= n; i++) {
        cin >> v[i];
        sums[i] = (sums[i-1] + v[i]);
    }

    ll result = 0;
    for(ll i = 1; i <= n; i++) {
        ll head = sums[i];

        ll rest = (sums[n] - head);

        ll start = upper_bound(sums.begin(), sums.end(), rest/2 + head) - sums.begin();
        ll end = lower_bound(sums.begin(), sums.end(), rest) - sums.begin();
        debug(i << ": " << start << " " << end);
        
        result += max((ll)0, end - start);
    }

    cout << result << "\n";

    return 0;
}

```