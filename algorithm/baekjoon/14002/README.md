# 14002
- [문제페이지](https://boj.kr/14002)

## 1) 문제 설명
수열이 주어졌을때, 몇개의 수를 제거하여 오름차순 정렬된 가장 긴 증가 수열의 길이와 그 값을 오름차순으로 출력하는 문제이다.

## 2) 문제 풀이
문제의 조건을 보면, n이 1000이기 때문에 $O(n^2)$ 풀이가 가능하다. 각 인덱스에 해당 수열 앞의 값 중 최고값에 +1한 값을 저장하면, 증가하는 부분수열을 구할 수 있다.

이때, 역추적을 사용하여야 값이 오름차순으로 출력된다.

## 3) 코드
```cpp
#define pii pair<int, int>
#define pll pair<ll, ll>

#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll n;
vector<ll> v(1010);
ll dp[1010];
ll track[1010];
vector<ll> result;

int main(int argc, char* argv[]) {
    fio; 

    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        dp[i] = 1;
    }

    for(ll i = 1; i <= n; i++) {
        ll maximum = LONG_LONG_MIN;
        ll index = -1;
        for(ll j = 1; j < i; j++) {
            if(maximum < dp[j]+1 && v[j] < v[i]) {
                maximum = dp[j]+1;
                index = j;
            }
        }
        if(index == -1) {
            continue;
        }

        track[i] = index;
        dp[i] = maximum; 
    }
    
    ll max_index = -1;
    ll maximum = LONG_LONG_MIN;
    for(int i = 1; i <= n; i++) {
        if(maximum < dp[i]) {
            maximum = dp[i];
            max_index = i;
        }
    }

    cout << maximum << "\n";
    
    for(ll i = max_index; i != 0; i = track[i]) {
        result.push_back(v[i]);
    }
    sort(result.begin(), result.end());
    for(ll i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << "\n";

    return 0;
}

```