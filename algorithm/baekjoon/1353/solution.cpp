typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define PRIME_SIZE 5
#define PIE M_PIf64
#define E M_E
#define ln(x) log(x)

#ifdef BOJ
#define debug(x)  ((void)0);
#define debug_value(x)  ((void)0);
#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);
#else
#define debug(x)  cout << "[Debug] " << x << "\n";
#define debug_value(x)  cout << "[Debug] " << #x << " is " << x << '\n';
#define fio ((void)0);
#endif

#define inf (1e10)

#include <bits/stdc++.h>

using namespace std;

ll S, P;

long double func(long double l) {
    errno = 0;
    ld result = pow(S/l, l);
    return errno == ERANGE || fetestexcept(FE_OVERFLOW)? inf : result;
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> S >> P;
    if(S == P) {
        cout << "1\n";
        return 0;
    }

    ld possible_multiply = func((double)S/E);

    if(possible_multiply < P) {
        cout << "-1\n";
        return 0;
    }

    ll left = 2;
    ll right = (ll)(S/E) + 1;

    while(right - left > 1) {
        ll mid = (left + right)/2;

        ld r = func(mid);

        if(r < P) {
            left = mid;
        }
        else {
            right = mid;
        }
    }
    if(func(left) >= P) {
        cout << left << "\n";
    }
    else {
        cout << right << "\n";
    }

    return 0;
}
