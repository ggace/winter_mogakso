# 11779
- [문제페이지](https://boj.kr/11779)

## 1) 문제 설명
시작점과 도착점이 주어질 때, 최소 거리를 출력하고, 최소거리 내에 있는 도시 개수와 도시를 출력하는 문제이다.

## 2) 문제 풀이
다익스트라를 사용해 최소 거리를 구하고, 이때, 역추적을 같이 사용하여 개수와 도시 번호를 출력하면 된다.

## 3) 코드
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

ll v, e;
ll s, t;
vector<vector<pll>> edges(1010);
ll weights[1010];
ll backtrack[1010];
vector<ll> result;

void dijkstra() {
    fill_n(weights, 1010, LONG_LONG_MAX);

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, s});
    weights[s] = 0;
    backtrack[s] = -1;

    while(!pq.empty()) {
        auto [cur_weight, cur_index] = pq.top();
        pq.pop();

        if(cur_weight != weights[cur_index]) continue;

        for(auto [next_index, next_weight] : edges[cur_index]) {
            if(cur_weight + next_weight >= weights[next_index]) {
                continue;
            }

            backtrack[next_index] = cur_index;
            weights[next_index] = cur_weight + next_weight;

            pq.push({cur_weight + next_weight, next_index});
        }
    }

    cout << weights[t] << "\n";
    for(ll i = t; i != -1; i = backtrack[i]) {
        result.push_back(i);
    }
    cout << result.size() << "\n";
    for(ll i = result.size()-1; i >= 0; i--) {
        cout << result[i] << " ";
    }
    cout << "\n";

}

int main() {
    cin >> v >> e;
    for(ll i = 0; i < e; i++) {
        ll a, b, c; cin >> a >> b >> c;
        edges[a].push_back({b, c});
    }
    cin >> s >> t;

    dijkstra();
}

```