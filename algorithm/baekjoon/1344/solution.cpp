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

vector<int> no_primes = {0,1,4,6,8,9,10,12,14,15,16,18};

int main(int argc, char* argv[]) {
    fio; 

    ll fact_18 = 1;
    for(int i = 1; i <= 18; i++) {
        fact_18 *= i;
    }
    
    ll a, b; cin >> a >> b;

    double result_a = 0;
    double result_b = 0;

    for(int i = 0; i < no_primes.size(); i++) {
        double percent_a_1 = 1;
        double percent_a_2 = 1;
        double percent_b_1 = 1;
        double percent_b_2 = 1;
        double combination_18_prime = fact_18;
        for(int j = 1; j <= no_primes[i]; j++) {
            combination_18_prime /= j;
            percent_a_1 *= (a/100.0);
            percent_b_1 *= (b/100.0);
        }
        for(int j = 1; j <= 18-no_primes[i]; j++) {
            combination_18_prime /= j;
            percent_a_2 *= (1.- a/100.0);
            percent_b_2 *= (1.- b/100.0);
        }

        result_a += combination_18_prime * percent_a_1 * percent_a_2;
        result_b += combination_18_prime * percent_b_1 * percent_b_2;
    }

    cout.precision(12);
    cout << 1.00 - result_a * result_b << "\n";

    return 0;
}
