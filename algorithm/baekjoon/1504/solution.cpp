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

ll fastpow(ll a, ll n, ll c){
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

vector<ll> prime_list;
bool is_prime[PRIME_SIZE+1] = {1,1,0}; // 0이 소수
void siv(ll n) {
    for(int i = 2; i <= n; i++) {
        if(!is_prime[i]) prime_list.push_back(i);
        for(auto p : prime_list) {
            if(i*p > n) break;
            is_prime[i*p] = true;
            if(i%p == 0) break;
        }
    }
}

ll v, e;

vector<vector<pll>> edges(20202);
ll weights[20202];

ll djikstra(ll s, ll q) {
    fill_n(weights, 20202, LONG_LONG_MAX);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, s});

    weights[s] = 0;
    while(!pq.empty()) {
        auto [cur_weight, cur_index] = pq.top();
        pq.pop();

        // debug(cur_index << " " << cur_weight << "=" << weights[cur_index]);

        if(cur_weight != weights[cur_index]) continue;

        for(auto [next, next_weight] : edges[cur_index]) {
            if(cur_weight + next_weight >= weights[next]) {
                continue;
            }
            weights[next] = cur_weight + next_weight;

            pq.push({cur_weight + next_weight, next});
        }
    }

    return weights[q];
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> v >> e;

    for(int i = 0; i < e; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v,w});
        edges[v].push_back({u,w});
    }


    ll s, q;
    cin >> s >> q;
    
    ll to_s = djikstra(1, s);
    ll to_q = djikstra(1, q);

    ll s_q = djikstra(s, q);

    ll from_s = djikstra(s, v);
    ll from_q = djikstra(q, v);

    if(to_s == LONG_LONG_MAX
    || to_q == LONG_LONG_MAX
    || s_q == LONG_LONG_MAX
    || from_s == LONG_LONG_MAX
    || from_q == LONG_LONG_MAX) {
        cout << -1 << "\n";
        return 0;
    }

    ll d1 = to_s + s_q + from_q;
    ll d2 = to_q + s_q + from_s;
    cout << min(d1, d2) << "\n";

    return 0;
}
