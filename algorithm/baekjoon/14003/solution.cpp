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

vector<pll> dp;
vector<ll> v = {0};
ll backtrack[1000005];
ll n;

int main(int argc, char* argv[]) {
    fio; 
    cin >> n;

    for(ll i = 1; i <= n; i++) {

        ll x; cin >> x;
        v.push_back(x);

        ll index = lower_bound(dp.begin(), dp.end(), pll(x, LONG_LONG_MIN)) - dp.begin();
        if(index != 0)
            backtrack[i] = dp[index-1].second;
        if(index == dp.size()) {
            dp.push_back({x, i});
            continue;
        }
        dp[index] = {x, i};
        
    }

    vector<ll> result;

    cout << dp.size() << "\n";
    for(ll i = dp[dp.size()-1].second; i != 0; i = backtrack[i]) {
        result.push_back(i);
    }
    for(ll i = result.size()-1; i >= 0; i--) {
        cout << v[result[i]] << " ";
    }
    cout << "\n";
    
    return 0;
}
