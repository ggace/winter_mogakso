# 2150
- [문제페이지](https://boj.kr/2150)

## 1) 문제 설명
그래프가 주어질때, 사이클이 이루어지는지를 판단해, 사이클의 노드 번호를 출력하면 된다.

## 2) 문제 풀이
SCC알고리즘을 사용한다. 그중, 코사라주 알고리즘을 사용했다. 정방향 dfs와 역방향 dfs하여 다시 돌아갈 수 있는지를 판단하면 된다.

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

ll v, e;
vector<vector<ll>> forward_edges(10101);
vector<vector<ll>> backward_edges(10101);
stack<ll> s;
bool visited[10101];
bool scc_visited[10101];

vector<vector<ll>> result(10101);

void dfs(ll i) {
    if(visited[i]) {
        return;
    }
    visited[i] = true;

    for(auto next : forward_edges[i]) {
        if(visited[next]) {
            continue;
        }
        dfs(next);
    }

    s.push(i);
}

void find_scc(ll index, ll cur) {
    if(scc_visited[cur]) {
        return;
    }
    scc_visited[cur] = true;

    result[index].push_back(cur);

    for(auto next : backward_edges[cur]) {
        if(scc_visited[next]) {
            continue;
        }
        find_scc(index, next);
    }
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> v >> e;

    for(ll i = 0; i < e; i++) {
        ll x, y; cin >> x >> y;

        forward_edges[x].push_back(y);
        backward_edges[y].push_back(x);
    }

    for(ll i = 1; i <= v; i++) {
        if(!visited[i]) {
            dfs(i);
        }
    }

    ll count = 0;
    while(!s.empty()) {
        ll cur = s.top();
        s.pop();
        if(scc_visited[cur]) {
            continue;
        }
        find_scc(count, cur);

        ++count;
    }

    cout << count << "\n";

    priority_queue<pll> pq;

    for(ll i = 0; i < count; i++) {
        sort(result[i].begin(), result[i].end());
        pq.push({-result[i][0], i});
    }

    while(!pq.empty()) {
        auto [_, index] = pq.top();
        pq.pop();

        for(auto value : result[index]) {
            cout << value << " ";
        }
        cout << "-1\n";
    }

    return 0;
}

```