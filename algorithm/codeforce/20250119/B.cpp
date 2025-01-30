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
    vector<pll> cards;

    ll n, m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ll x;
            cin >>x;
            cards.push_back({x, i});
        }
    }

    sort(cards.begin(), cards.end());

    vector<ll> start_list;
    vector<bool> visited(n, 0);
    for(int i=0; i < n; i++) {
        // debug(i << " " << cards[i].second);
        if(visited[i]) {
            cout << "-1\n";
            return;
        }
        visited[i] = true;
        start_list.push_back(cards[i].second);
    }

    for(ll i = n; i < cards.size(); i++) {
        // debug(i << " " << cards[i].second);
        if(start_list[(i % n)] != cards[i].second) {
            cout << "-1\n";
            return;
        }
    }

    for(int i = 0; i < n; i++) {
        cout << start_list[i]+1 << " ";
    }
    cout << "\n";



}

int main(int argc, char* argv[]) {
    fio; 

    ll t;
    cin >> t;

    while(t--) {
        solution();
    }

    return 0;
}
