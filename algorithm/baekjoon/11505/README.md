# 2042
- [문제 페이지](https://boj.kr/2042)

## 문제 설명
각 인덱스의 값이 처음에 주어진다.

1 a b가 입력될 시, a번째 값을 b로 수정하고, 

2 a b가 입력될 시, a부터 b까지의 곱을 출력한다.(1000000007로 나눈값을 출력한다.)

## 문제 해설
세그먼트 트리 구현 확인을 위해 푼 문제이다. 

- [세그먼트 트리 페이지](/algorithm/study/segtree/README.md)

## 코드
```cpp
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define PRIME_SIZE 5
#define PIE M_PIf64

#define BOJ

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

enum CONSTANT {
    INVALID = LONG_LONG_MIN,
    REST = 1'000'000'007
};

vector<ll> segtree;
ll seg_depth;

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
ll fastpow(ll a, ll n){
    ll result=1;
    while(n){
        if(n&1){
            result *=a;
        }
        a*=a;
        n>>=1;
    }
    return result;
}

void resize(ll size) {
    ll depth = ceil(log2(size));
    ll real_size = fastpow(2, depth+1);
    segtree.resize(real_size);
    seg_depth = depth;
    
    for(ll i = 0; i < real_size; i++) {
        segtree[i] = 1;
    }
}

void update_value(ll index, ll value) {
    ll real_index = fastpow((ll)2, seg_depth) + index;
    ll cur_value = segtree[real_index];
    ll reciprocal_cur_value = fastpow_with_modular(cur_value, REST-2, REST);
    
    segtree[real_index] = value % REST;

    while(true) {
        real_index /= 2;
        segtree[real_index] = (segtree[2*real_index] * segtree[2*real_index+1]) % REST;
        
        if(real_index == 1) {
            break;
        }
    }
}

ll get_value(ll start, ll end) {
    queue<pll> q;
    ll possible_range = fastpow(2, seg_depth);
    start = possible_range + start;
    end = possible_range + end;

    ll result = 1;
    
    q.push({1, possible_range});
    while(!q.empty()) {
        auto [cur_index, cur_possible_range] = q.front();
        q.pop();

        ll left = cur_index * cur_possible_range;
        ll right = (cur_index + 1) * cur_possible_range - 1;

        if(start <= left && right <= end) {
            result *= (segtree[cur_index] % REST);
            result %= REST;
            continue;
        }
        if(end < left || start > right) {
            continue;
        }
        ll next_index = cur_index * 2;
        if(next_index >= segtree.size()) {
            continue;
        }
        
        q.push({next_index, cur_possible_range/2});
        q.push({next_index+1, cur_possible_range/2});

    }   

    return result;
}

ll m, n, k;

int main(int argc, char* argv[]) {
    fio; 
    cin >> n >> m >> k;

    resize(n+1);

    for(ll i = 0; i < n; i++) {
        ll value;
        cin >> value;
        update_value(i, value);
    }

    for(ll i = 0; i < m+k; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        switch(a) {
            case 1:
                update_value(b-1, c);
                break;
            case 2:
                cout << get_value(b-1, c-1) << "\n";
                break;
        }
    }


    return 0;
}

```