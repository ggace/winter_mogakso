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

void solution() {
    map<ll, ll> arr;

    ll a1, a2, a3, a4;
    cin >> a1 >> a2 >> a3 >> a4;

    ++arr[a1 + a2];
    ++arr[a3-a2];
    ++arr[a4-a3];

    ll result = LONG_LONG_MIN;
    for(auto iter= arr.begin(); iter!= arr.end(); iter++) {
        result = max(result, iter->second);
    }
    cout << result << "\n";

}

int main(int argc, char* argv[]) {
    fio; 

    ll t; cin >> t;

    while(t--) {
        solution();
    }

    return 0;
}
