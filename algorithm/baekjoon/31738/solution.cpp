#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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

int main() {
    ll n, m; cin >> n >> m;

    if(n >= m) {
        cout << "0\n";
        return 0;
    }

    ll r = n / m;

    ll result = 1;
    for(int i = 1; i <= m; i++) {
        ll t = r;
        if(i <= n % m) {
            t++;
        }
        result *= fastpow(i % m, t, m);
        result %= m;
    }
    cout << result << "\n";

}