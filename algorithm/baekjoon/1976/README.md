# 1976
- [문제페이지](https://boj.kr/1976)

## 1) 문제 설명
엣지가 주어지며, 해당 정점끼리 연결될 수 있는지를 판단하는 문제이다.

## 2) 문제 풀이
union find 문제이다. 그래프가 주어질 것이다. visited를 사용해 tree구조를 구성한다. 정점이 한 집합으로 연결되어 있다면, yes를 출력하고, 아니라면 no를 출력하면 된다.

## 3) 코드
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

ll n, m;

vector<vector<ll>> edges;
vector<ll> plan;

bool visited[222];
ll parent[222];

ll find(ll index) {
    if(parent[index] == index) {
        return index;
    }
    return parent[index] = find(parent[index]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);

    parent[b] = a;
}

int main() {
    cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            if(x)
                Union(i, j);
        }
    }

    ll result = -1;
    
    for(int i = 0; i < m; i++) {
        int d;
        cin >> d;

        if(result == -1) {
            result = find(d);
        }

        if(result != find(d)) {
            cout << "NO\n";
            return 0;
        }
        
    }
    cout << "YES\n";
}

```