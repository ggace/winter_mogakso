typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define println(s) cout << s << "\n"
#define mp() make_pair()
#define PRIME_SIZE 5
#define PIE M_PIf64

#ifdef BOJ
#define debug(x)  ((void)0);
#define debug_value(x)  ((void)0);
#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);
#else
#define debug(x)  cout << "[Debug] " << x;
#define debug_value(x)  cout << "[Debug] " << #x << " is " << x << '\n';
#define fio ((void)0);
#endif

#include <bits/stdc++.h>

using namespace std;

struct Direction {
    ll dx;
    ll dy;
};

struct Position {
    ll x;
    ll y;
};

ll fastpow_with_modular(ll a, ll n, ll c){
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

int main(int argc, char* argv[]) {
    fio; 

    int t;
    cin >> t;

    while(t--) {
        ll result = 1;

        ll x;
        cin >> x;

        if(x == 1) {
            cout << "5\n";
            continue;
        }

        result = fastpow_with_modular(5, x-1, 1000000007);
        result *= 4;
        result %= 1000000007;

        cout << result << "\n";
    }

    return 0;
}
