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

ll n;
vector<ll> v;
vector<ll> sums;

int main(int argc, char* argv[]) {
    fio; 

    cin >> n;
    v.resize(n+1);
    sums.resize(n+1);

    for(ll i = 1; i <= n; i++) {
        cin >> v[i];
        sums[i] = (sums[i-1] + v[i]);
    }

    ll result = 0;
    for(ll i = 1; i <= n; i++) {
        ll head = sums[i];

        ll rest = (sums[n] - head);

        ll start = upper_bound(sums.begin(), sums.end(), rest/2 + head) - sums.begin();
        ll end = lower_bound(sums.begin(), sums.end(), rest) - sums.begin();
        debug(i << ": " << start << " " << end);
        
        result += max((ll)0, end - start);
    }

    cout << result << "\n";

    return 0;
}
