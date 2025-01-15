# 2042
- [문제 페이지](https://boj.kr/2357)

## 문제 설명
각 인덱스의 값이 처음에 주어진다.

a b가 입력될 시, a부터 b까지의 최솟값과 최댓값을 출력한다.

## 문제 해설
세그먼트 트리 구현 확인을 위해 푼 문제이다. 

- [세그먼트 트리 페이지](/algorithm/study/segtree/README.md)

## 코드
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

ll fastpow_with_modular(ll a, ll n, ll c){
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

vector<array<ll, 2>> segtree;
ll segdepth;

void initialize(ll size) {
    ll depth = ceil(log2(size));
    ll real_size = pow(2, depth+1)+1;
    segtree.resize(real_size);
    segdepth = depth;

    for(ll i = 0; i < real_size; i++) {
        segtree[i] = {LONG_LONG_MAX, LONG_LONG_MIN};
    }
}

void update(ll index, ll value) {
    ll real_index = pow(2, segdepth) + index;
    segtree[real_index] = {value, value};
    while(true) {
        real_index /= 2;
        segtree[real_index][0] = min(segtree[real_index*2][0], segtree[real_index*2+1][0]);
        segtree[real_index][1] = max(segtree[real_index*2][1], segtree[real_index*2+1][1]);
        
        if(real_index == 1) {
            break;
        }
    }
}

array<ll, 2> get_value(ll start, ll end) {
    array<ll, 2> result = {LONG_LONG_MAX, LONG_LONG_MIN};
    ll possible_range=pow(2, segdepth);
    start += possible_range;
    end += possible_range;

    queue<pll> q;
    q.push({1, possible_range});

    while(!q.empty()) {
        auto [index, possible_range] = q.front();
        q.pop();

        ll left = index*possible_range;
        ll right = (index +1) * possible_range-1;

        if(start <= left && right <= end) {
            result= {
                min(result[0], segtree[index][0]),
                max(result[1], segtree[index][1])
            };
            continue;
        }

        if(end < left || right < start) {
            continue;
        }
        ll next_index = index*2;

        if(next_index >= segtree.size()) {
            continue;
        }
        q.push({next_index, possible_range/2});
        q.push({next_index+1, possible_range/2});
    }

    return result;
}

ll n, m;

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> m;

    initialize(n);

    for(ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        update(i, x);
    }
    
    while(m--) {
        ll a, b;
        cin >> a>> b;


        auto result = get_value(a-1, b-1);

        cout << result[0] << " " << result[1] << "\n";
    }

    return 0;
}

```