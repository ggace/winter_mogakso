# 14003
- [문제페이지](https://boj.kr/14003)

## 1) 문제 설명
수열이 주어졌을때, 몇개의 수를 제거하여 오름차순 정렬된 가장 긴 증가 수열의 길이와 그 값을 오름차순으로 출력하는 문제이다.

## 2) 문제 풀이
n이 $1,000,000$ 이하이기 때문에 $n\log n$ 알고리즘을 사용해야한다.

lower_bound를 사용하여 오름차순 정렬된 배열의 값을 갱신하며 lis를 구하면 된다.

이때, 역추적을 사용하여 출력하면 된다.

## 3) 코드
```cpp
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

vector<pll> dp;
vector<ll> v = {0};
ll backtrack[1000005];
ll n;

int main(int argc, char* argv[]) {
    fio; 
    cin >> n;

    for(ll i = 1; i <= n; i++) {

        ll x; cin >> x;
        v.push_back(x);

        ll index = lower_bound(dp.begin(), dp.end(), pll(x, LONG_LONG_MIN)) - dp.begin();
        if(index != 0)
            backtrack[i] = dp[index-1].second;
        if(index == dp.size()) {
            dp.push_back({x, i});
            continue;
        }
        dp[index] = {x, i};
        
    }

    vector<ll> result;

    cout << dp.size() << "\n";
    for(ll i = dp[dp.size()-1].second; i != 0; i = backtrack[i]) {
        result.push_back(i);
    }
    for(ll i = result.size()-1; i >= 0; i--) {
        cout << v[result[i]] << " ";
    }
    cout << "\n";
    
    return 0;
}

```