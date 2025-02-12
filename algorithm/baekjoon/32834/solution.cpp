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

ll n;

vector<array<ll, 2>> bins;
vector<array<ll, 3>> result;

void initialize(ll t) {
    bins.resize(t+1);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            bins[i+1][j] = n-i;
        }
    }
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n;

    initialize(n);

    ll index = 1;
    while(true) {
        for(int i = index; i < n; i++) {
            auto b1 = bins[i].begin();
            auto b2 = bins[i+1].begin();
            b2 ++;
            cout << i << " " << *b1 << " " << *b2 << "\n";
            swap(b1, b2);
        }
        break;
    }

    return 0;
}
