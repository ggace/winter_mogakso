#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ll a, b; cin >> a >> b;

    cout << (int)(a / b) << ".";


    for(int i = 0; i < 1000; i++) {
        a %= b;
        a *= 10;
        cout << (int)(a/b);
    }
    cout << "\n";
}