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

vector<ll> dp;

ll n;

int main(int argc, char* argv[]) {
    fio; 
    cin >> n;

    while(n--) {

        ll x; cin >> x;

        ll index = lower_bound(dp.begin(), dp.end(), x) - dp.begin();
        
        if(index == dp.size()) {
            dp.push_back(x);
            continue;
        }

        dp[index] = min(x, dp[index]);
    }

    cout << dp.size() << "\n";
    
    return 0;
}
