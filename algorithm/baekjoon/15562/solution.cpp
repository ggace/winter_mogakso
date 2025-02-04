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

vector<vector<ll>> parents(1010101);
vector<vector<ll>> childs(1010101);
ll depths[1010101];

bool is_visited[1010101];

int main(int argc, char* argv[]) {
    fio; 

    ll n, m;
    cin >> n >> m;

    for(ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;

        parents[b].push_back(a);
        childs[a].push_back(b);
    }

    ll result = 0;

    queue<ll> q;
    
    for(int i = 1; i <= n; i++) {
        if(parents[i].empty()) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        ll cur_index = q.front();
        q.pop();

        for(auto child : childs[cur_index]) {
            if(is_visited[child]) {
                continue;
            }
            q.push(child);
            is_visited[child] = true;
            result++;
        }

        debug(cur_index <<  ": " << result);
    }

    cout << result << "\n";

    return 0;
}
