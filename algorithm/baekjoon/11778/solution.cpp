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

#define REST 1'000'000'007

vector<vector<vector<ll>>> fibonacci(66, vector<vector<ll>>(2, vector<ll>(2)));

vector<vector<ll>> multiplyMatrix(vector<vector<ll>> a, vector<vector<ll>> b) {
    vector<vector<ll>> result(2, vector<ll>(2, 0));
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                result[i][j] += (a[i][k] * b[k][j]) % REST;
                result[i][j] %= REST;
            }
        }
    }
    return result;
}

void initialize() {
    fibonacci[0] = {{1,0}, {0,0}};
    fibonacci[1] = {{1,1}, {1,0}};
    for(int i = 2; i < 64; i++) {
        fibonacci[i] = multiplyMatrix(fibonacci[i-1], fibonacci[i-1]);
    }
}

ll get_fibonacci(ll n) {
    vector<vector<ll>> result = {{1,0}, {0,1}};
    for(ll i = 1; n; i++) {
        if(n & 1) {
            result = multiplyMatrix(result, fibonacci[i]);
        }

        n >>= 1;
    }

    return result[0][1] % REST;
}

ll gcd(ll a, ll b) {
    if(b == 0) {
        return a;
    }
    return gcd(b, (a % b));
}

int main(int argc, char* argv[]) {
    // fio; 

    initialize();

    ll a, b; cin >> a >> b;

    if(a < b) {
        swap(a, b);
    }

    cout << get_fibonacci(gcd(a, b));

    return 0;
}
