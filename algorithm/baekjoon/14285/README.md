# 14285
- [문제페이지](https://boj.kr/14285)

## 1) 문제 설명
무방향 그래프가 주어진다. 이때, 간선을 하나씩 제거할 때, 비연결되는 시점의 가중치 합이 최댓값을 출력한다.

## 2) 문제 풀이
다익스트라를 사용해 문제를 풀 수 있다. 이때, 해당 엣지를 지운것과 사용한 것을 함께 다익스트라를 돌리고, 전체 합에서 다익스트라의 값을 뺀 값을 출력하면 된다.

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

struct Edge {
    ll to;
    ll weight;
};

struct Node {
    ll index;
    ll weight;
    bool erase;

    bool operator<(const Node& node)const {

        return weight > node.weight;
    }
};

ll n, m;
vector<vector<Edge>> edges(5050);
ll s, t;
vector<vector<ll>> weights(5050);
ll sum_weights;

void dkelr(ll start) {
    priority_queue<Node> pq;
    pq.push({start, 0, 0});

    while(!pq.empty()) {
        auto [cur_index, cur_weight, is_erased] = pq.top();
        pq.pop();

        debug(cur_index << " " << cur_weight << " - " << is_erased);

        if(cur_index == t && is_erased == 1) {
            cout << sum_weights - cur_weight << "\n";
            break;
        }

        for(auto [next_to, next_weight] : edges[cur_index]) {
            if(!is_erased && cur_weight < weights[next_to][is_erased]){
                weights[next_to][1] = cur_weight;
                pq.push({next_to, cur_weight, 1});
            }

            if(cur_weight + next_weight > weights[next_to][is_erased]) {
                continue;
            }
            weights[next_to][is_erased] = cur_weight + next_weight;
            pq.push({next_to, cur_weight + next_weight, is_erased});
            
        }
    }
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> m;

    for(ll i = 0; i <= n; i++) {
        weights[i].push_back(LONG_LONG_MAX);
        weights[i].push_back(LONG_LONG_MAX);
    }

    for(int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a>> b >> c;
        edges[a].push_back({b,c});
        edges[b].push_back({a,c});

        sum_weights += c;
    }

    debug(sum_weights)

    cin >> s >> t;

    dkelr(s);

    return 0;
}

```