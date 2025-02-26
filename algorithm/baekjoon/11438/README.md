# 11438
- [문제페이지](https://boj.kr/11438)

## 1) 문제 설명
lca문제이다.

## 2) 코드
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

ll n, m;
vector<vector<ll>> edges(101010);
bool tree_visited[101010];
ll parent[101010][22];
ll tree_depth[101010];

void make_tree(ll start) {
    queue<pll> q;
    
    q.push({start, 1});
    tree_visited[start] = true;
    tree_depth[start] = 1;

    while(!q.empty()) {
        auto [cur_node, cur_depth] = q.front();
        q.pop();

        for(auto next_node : edges[cur_node]) {
            
            if(tree_visited[next_node]) {
                continue;
            }
            q.push({next_node, cur_depth+1});
            tree_visited[next_node] = true;
            tree_depth[next_node] = cur_depth+1;

            parent[next_node][0] = cur_node;
            ll head = cur_node;
            for(ll i = 1; i <= 20; i++) {
                if(parent[i-1] == 0) break;
                parent[next_node][i] = parent[parent[next_node][i-1]][i-1];
            }
        }
    }
}

void lca(ll x, ll y) {
    ll x_depth = tree_depth[x];
    ll y_depth = tree_depth[y];

    if(x_depth - y_depth < 0) {
        swap(x_depth, y_depth);
        swap(x, y);
    }

    ll depth_diff = x_depth - y_depth;

    for(int i = 0; depth_diff; i++) {
        if(depth_diff & 1) {
            x = parent[x][i];
        }
        depth_diff >>= 1;
    }
    
    if(x == y) {
        cout << x << "\n";
        return;
    }

    for (ll i = 20; i >= 0; i--) { 
        if (parent[x][i] != parent[y][i]) {
            x = parent[x][i];
            y = parent[y][i];
        }
    }

    cout << parent[x][0] << "\n";
}

int main() {
    fio;
    cin >> n;
    for(ll i = 0; i < n-1; i++) {
        ll x, y;
        cin >> x >> y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    make_tree(1);

    cin >> m;
    
    while(m--) {
        ll x, y;
        cin >> x >> y;

        lca(x, y);
    }
}
```