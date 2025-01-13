# 17951
- [문제 페이지](https://boj.kr/17951)

## 1) 문제 설명
시험지 개수 n과 시험지를 나눌 그룹 k가 있을때, 주어진 n개의 시험지의 점수를 k개의 그룹으로 나눠 그 최솟값의 점수가 가장 크도록 해야하는 문제이다.

## 2) 문제 해설

기본적인 발상은 다음과 같다. 먼저 left를 0, right를 각 시험지의 점수 합으로 둔다.

이때, target을 $\frac{(left + right)}{2}$로 둔다.

이후 시험지에서 target 이상인 부분으로 k번 나눈다. 

만약 k번으로 나눌 수 있다면 target은 더 커질수 있기 때문에 left를 이전 target으로, k번으로 나눌 수 없다면 target값이 이보다 작아야 하기 때문에 right를 target으로 정해 더 작아질 수 있게 한다.

이를 반복하여 left와 right가 같아지는 지점을 찾게 되면 이 값은 시험지를 k로 나눴을 때의 최저값중 가장 큰 값이라고 할 수 있다.

따라서, 이를 출력하면 원하는 결과를 얻을 수 있다.

### 3) 코드
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
#define debug(x)  cout << "[Debug] " << x << "\n";
#define debug_value(x)  cout << "[Debug] " << #x << " is " << x << '\n';
#define fio ((void)0);
#endif

#include <bits/stdc++.h>

using namespace std;

ll n, k;
ll sums[101010] = {0, };

ll find_target(ll start, ll target) {
    if(target > sums[n] - sums[start-1]) {
        return -1;
    }
    // debug("[find_target]: " << (target + sums[start-1]));
    return lower_bound(sums+start, sums+n, target + sums[start-1]) - sums;
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> k;

    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sums[i] = sums[i-1] + x;
    }

    ll left = 1, right = sums[n]+1;
    ll cur_target;
    while(left < right - 1) {
        cur_target = (left + right)/2;
        
        ll start_index = 1;
        bool is_too_much = false;
        for(ll i = 0; i < k; i++) {
            
            ll next_index = find_target(start_index, cur_target);
            if(next_index == -1) {
                is_too_much = true;
                break;
            }
            ++next_index;
            start_index = next_index;
        }

        if(is_too_much) {
            right = cur_target;
        }
        else {
            left = cur_target;
        }
    }

    cout << left << "\n";

    return 0;
}   
```