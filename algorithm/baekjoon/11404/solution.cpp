#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

ll n;
ll m;

ll result[111][111];

void floid(){

    for(ll k = 1; k <= n; k++) {
        for(ll i = 1; i <= n; i++) {
            for(ll j = 1; j <= n; j++) {
                result[i][j] = min(result[i][j], result[i][k] + result[k][j]);
            }
        }
    }
            
}

int main() {
    for(ll i = 1; i < 111; i++) {
        for(ll j = 1; j < 111; j++) {
            result[i][j] = i==j? 0: (ll)(1e10);
        }
    }
                
    cin >> n >> m;

    for(ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        result[a][b] = min(c, result[a][b]);
    }

    floid();

    for(ll i= 1; i <= n;i++) {
        for(ll j = 1; j <= n; j++) {
            cout << result[i][j] << " ";
        }
        cout << "\n";
    }
}
