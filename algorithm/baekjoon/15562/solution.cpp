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

bool is_possible[1010101];

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

    queue<array<ll, 2>> q;
    
    for(int i = 1; i <= n; i++) {
        if(parents[i].empty()) {
            q.push({i, 0});
        }
    }

    while(!q.empty()) {
        auto [cur_index, cur_depth] = q.front();
        q.pop();

        
        
        is_possible[cur_index] = true;
        depths[cur_index] = cur_depth;

        ll push_count = 0;

        for(ll next_index : childs[cur_index]) {
            bool is_push = true;
            bool is_root = false;
            ll count = 0;
            for(ll root_of_next_index : parents[next_index]) {
                if(!is_possible[root_of_next_index]) {
                    is_push = false;
                    break;
                }
                else if(depths[root_of_next_index] == cur_depth) {
                    ++count;
                }

                if(depths[root_of_next_index] == 0) {
                    is_root = true;
                }
            }
            if(is_push) {
                q.push({next_index, cur_depth + 1});
                result += count;
                depths[next_index] = cur_depth+1;
                ++push_count;
            }
            
        }

        if(!push_count && cur_depth == 0) {
            q.push({cur_index, cur_depth+1});
            depths[cur_index] = cur_depth+1;
            is_possible[cur_index] = false;
        }

        debug(cur_index << " " << cur_depth << ": " << result);
    }

    cout << result << "\n";

    return 0;
}
