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
ll s;
vector<vector<pll>> edges(20202);
ll weights[20202];

int main(int argc, char* argv[]) {
    fio; 
    fill_n(weights, 20202, LONG_LONG_MAX);

    cin >> v >> e;

    cin >> s;

    for(int i = 0; i < e; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v,w});
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, s});

    weights[s] = 0;
    while(!pq.empty()) {
        auto [cur_weight, cur_index] = pq.top();
        pq.pop();

        debug(cur_index << " " << cur_weight << "=" << weights[cur_index]);

        if(cur_weight != weights[cur_index]) continue;

        for(auto [next, next_weight] : edges[cur_index]) {
            if(cur_weight + next_weight >= weights[next]) {
                continue;
            }
            weights[next] = cur_weight + next_weight;

            pq.push({cur_weight + next_weight, next});
        }
    }

    for(ll i = 1; i <= v; i++) {
        if(weights[i] != LONG_LONG_MAX) {
            cout << weights[i] << "\n";
        }
        else {
            cout << "INF\n";
        }
        
    }

    return 0;
}
