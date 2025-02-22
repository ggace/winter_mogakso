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

bool isPrime(ll n) {
    if(n < 2) {
        return false;
    }
    for(ll i =2; i * i <= n; i++) {
        if(n % i ==0) {
            return false;
        }
    }
    return true;
}

void solution() {
    ll x; cin >> x;

    for(ll i = x; ; i++) {
        // debug(i);
        if(isPrime(i)) {
            cout << i << "\n";
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    fio; 

    ll t; cin >> t;

    while(t--) {
        solution();
    }

    return 0;
}
