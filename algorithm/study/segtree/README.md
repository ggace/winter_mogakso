# 세그먼트 트리

## 기본 개념
자식 노드의 합을 부모노드의 값으로 하는 트리이다.

## 방법
많은 방법이 있겠지만, 난 다음과 같은 방법으로 세그먼트 트리를 구성했다.

- 이진 트리를 배열을 사용해 구현시 부모노드의 인덱스가 i라면 자식노드는 $i \times 2$, $i \times 2 + 1$이다. 

## 함수
### 1. resize
- n개의 값을 저장하기 위해 필요한 배열의 크기를 재조정하기 위한 함수.
- n개의 노드를 저장해야 할 때, $2^{\lceil log_2{n} \rceil + 1}$ 으로 정한다.
- tree의 깊이는 $\lceil log_2{n} \rceil$ 이다.(인덱스 1의 높이가 0이다.)

### 2. update_value
- 특정 index의 값을 value로 변경하기 위한 함수.
1. 주어진 index와 segtree의 depth값을 사용해 주어진 index가 실제 가리키는 배열상의 위치를 구한다.
2. 해당 위치의 값과 입력된 value의 차이를 저장한다.
3. 위치가 1이 될때까지, 인덱스 값에 차이만큼을 더하고 인덱스를 2로 나눈다.
4. 모든 과정이 종료될때, 입력된 index와 연결된 모든 값이 그 값에 맞춰 변경되어 있음을 알 수 있다.

### 3. get_value
- 특정 구간이 주어질 시, 이 구간에서의 합을 구하기 위한 함수.
1. 인덱스를 1에서부터 시작한다.
2. 인덱스에서 갈 수 있는 노드가 입력된 구간 내에 존재한다면 해당 값을 결과값에 더한다.
3. 인덱스에서 갈 수 있는 노드가 입력된 구간에서 벗어날 때, 해당 방향으로 확인 과정을 멈춘다.
4. 만약 구간과 갈수 있는 노드가 걸칠시, 자식 노드로 이동해 같은 과정을 반복한다.

## 코드
```c
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
    INVALID = LONG_LONG_MIN
};

vector<ll> segtree;
ll seg_depth;

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
    segtree.resize(fastpow(2, depth+1));
    seg_depth = depth;
}

void update_value(ll index, ll value) {
    ll real_index = fastpow(2, seg_depth) + index;
    if(real_index >= segtree.size()) {
        return;
    }
    ll cur_value = segtree[real_index];
    ll value_change = value - cur_value;
    while(true) {
        segtree[real_index] += value_change;
        if(real_index == 1) {
            break;
        }
        real_index /= 2;
    }
}

ll get_value(ll start, ll end) {
    ll prev_index = fastpow(2, seg_depth);
    start = prev_index + start;
    end = prev_index + end;

    ll result = 0;

    ll index = 1;
    queue<pll> q;
    q.push({index, 0});
    while(!q.empty()) {
        auto [cur_index, cur_depth] = q.front();
        q.pop();
        debug(cur_index << " " << cur_depth);

        ll possible_range = fastpow(2, seg_depth - cur_depth);

        ll left = cur_index * possible_range;
        ll right = (cur_index + 1) * possible_range - 1;

        debug(left << " <-> " << right);

        if(start <= left && right <= end) {
            debug("possible at " << cur_index);
            result += segtree[cur_index];
            continue;
        }
        if(end < left) {
            continue;
        }
        if(start > right) {
            continue;
        }
        ll next_index = cur_index * 2;
        if(next_index >= segtree.size()) {
            continue;
        }
        
        q.push({next_index, cur_depth+1});
        q.push({next_index+1, cur_depth+1});

    }
    

    return result;
}

int main(int argc, char* argv[]) {
    fio; 

    return 0;
}
```