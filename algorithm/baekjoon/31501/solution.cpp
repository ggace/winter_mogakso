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

ll D[3030];
ll n, q;
vector<vector<ll>> edges(3030);
ll result[3030];

ll dfs(ll start, ll depth) {
    debug(start << " " <<  depth);
    ll temp_result = depth;
    
    for(auto next : edges[start]) {
        temp_result = max(dfs(next, depth+1), temp_result);
    }

    return result[start] = max(temp_result, result[start]);
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> q;

    for(ll i = 0; i < n;i++) {
        cin >> D[i];
        
        for(ll j = 0; j < i; j++) {
            if(D[i] > D[j]) {
                edges[j].push_back(i);
            }
        }
    }

    for(ll i = 0; i < n;i++) {
        if(edges[i].empty())
            dfs(i, 1);
    }

    while(q--) {
        ll x; cin >> x;
        cout << result[x-1] << "\n";
    }

    return 0;
}
