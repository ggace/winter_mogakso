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

void solution() {
    ll n, m1, m2; cin >> n >> m1 >> m2;
    set<pll> edges;

    for(ll i = 0; i < m1+m2; i++) {
        ll x, y;
        cin >> x >> y;
        ll a = max(x,y);
        ll b = min(x,y);

        if(a==b) {
            continue;
        }

        if(edges.find({a,b}) != edges.end()) {
            edges.erase({a,b});
        }
        else {
            edges.insert({a,b});
        }
    }
    cout << edges.size() << "\n";
}

int main(int argc, char* argv[]) {
    fio; 

    ll t; cin >> t;
    while(t--) {
        solution();
    }

    return 0;
}
