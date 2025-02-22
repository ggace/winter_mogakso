#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);
typedef long long ll;
typedef unsigned long long ull;

#include <bits/stdc++.h>

using namespace std;

vector<ll> v;
vector<ll> unique_v;

int main(){
    fio;

    ll n;
    cin >> n;

    for(ll i = 0; i < n; i++) {
        ll a;
        cin >> a;
        v.push_back(a);
        unique_v.push_back(a);
    }

    sort(unique_v.begin(), unique_v.end());
    unique_v.erase(unique(unique_v.begin(), unique_v.end()), unique_v.end());

    for(ll i = 0; i < v.size() ;i++) {
        ll index = (lower_bound(unique_v.begin(), unique_v.end(), v[i]) - unique_v.begin());
        cout << index << " ";
    }
    cout << "\n";

    return 0;
}
