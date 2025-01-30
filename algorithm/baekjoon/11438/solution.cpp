typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define PRIME_SIZE 5
#define PIE M_PIf64

#define BOJ

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

ll n;
vector<vector<ll>> edges(101010);
bool visited[101010];

ll parents[101010][64];
ll depth_list[101010];

struct Node {
    ll index;
    ll parent;
    ll depth;
};

void bfs(ll root) {
    queue<Node> q;
    q.push({root, 0, 1});
    visited[root] = true;

    while(!q.empty()) {
        auto [cur_index, cur_parent, cur_depth] = q.front();
        q.pop();

        depth_list[cur_index] = cur_depth;
        parents[cur_index][0] = cur_parent;

        ll head = cur_parent;
        for(ll i = 1; i <= 20; i++) {
            parents[cur_index][i] = parents[head][i-1];            
            head = parents[cur_index][i];
        }

        for(auto next: edges[cur_index]) {
            if(visited[next]) {
                continue;
            }
            visited[next] = true;
            q.push({next, cur_index, cur_depth+1});
        }
    }
}

void lca(ll x, ll y, ll depth_diff) {

    // cout << x << " " << y << "\n";
    for(ll i = 0; depth_diff; i++) {

        if(depth_diff & 1) {
            y = parents[y][i];
        }


        depth_diff >>= 1;
    }
    // cout <<x << " "  << y << "\n";
    while(x != y) {
        for(ll i = 19; i >= 0; i--) {
            if(parents[x][i] != parents[y][i] && parents[x][i] != 0 && parents[y][i] != 0) {
                // cout << x << " " << y << "\n";
                x = parents[x][i];
                y = parents[y][i];
                // cout << x << " " << y << "\n";
            }
        }
        if(x != y) {

            x = parents[x][0];
            y = parents[y][0];
        }
    }
    cout << x << "\n";
}

int main(int argc, char* argv[]) {
    // fio; 

    cin >> n;

    for(ll i = 0; i < n-1; i++) {
        ll a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    bfs(1);

    ll m;
    cin >> m;

    // for(ll i = 1; i <= n; i++) {
    //     cout << i << " : " ;
    //     for(ll j = 0; j < n; j++) {
    //         cout << parents[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    while(m--) {
        ll x, y;
        cin >> x >> y;

        if(depth_list[x] > depth_list[y]) { // x의 depth가 항상 작음. y가 올라가야됨.
            swap(x, y);
        }

        lca(x, y, depth_list[y] - depth_list[x]);
    }

    return 0;
}
