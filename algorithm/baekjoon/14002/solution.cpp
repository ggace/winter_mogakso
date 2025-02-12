#define pii pair<int, int>
#define pll pair<ll, ll>

#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll n;
vector<ll> v(1010);
ll dp[1010];
ll track[1010];
vector<ll> result;

int main(int argc, char* argv[]) {
    fio; 

    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        dp[i] = 1;
    }

    for(ll i = 1; i <= n; i++) {
        ll maximum = LONG_LONG_MIN;
        ll index = -1;
        for(ll j = 1; j < i; j++) {
            if(maximum < dp[j]+1 && v[j] < v[i]) {
                maximum = dp[j]+1;
                index = j;
            }
        }
        if(index == -1) {
            continue;
        }

        track[i] = index;
        dp[i] = maximum; 
    }
    
    ll max_index = -1;
    ll maximum = LONG_LONG_MIN;
    for(int i = 1; i <= n; i++) {
        if(maximum < dp[i]) {
            maximum = dp[i];
            max_index = i;
        }
    }

    cout << maximum << "\n";
    
    for(ll i = max_index; i != 0; i = track[i]) {
        result.push_back(v[i]);
    }
    sort(result.begin(), result.end());
    for(ll i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << "\n";

    return 0;
}
