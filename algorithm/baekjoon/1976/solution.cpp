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
