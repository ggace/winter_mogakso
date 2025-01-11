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
#define debug(x)  cout << "[Debug] " << x << "\n";
#define debug_value(x)  cout << "[Debug] " << #x << " is " << x << '\n';
#define fio ((void)0);
#endif

#include <bits/stdc++.h>

using namespace std;

ll n, m, k;

enum constant{
    EQUAL = -1,
    OVER = -2,
    DEFAULT = -3
};

set<pll> database;

pll find_close_data_key(ll key) {
    auto iter = database.lower_bound({key, -1});
    pll data1 = *iter;
    pll data2;
    if(iter == database.begin()) {
        data2 = {LONG_LONG_MAX, LONG_LONG_MAX};
    }
    else {
        data2= *(--iter);
    }

    ll diff1= abs(data1.first - key);
    ll diff2= abs(data2.first - key);

    if(diff1 > k && diff2 > k) {
        return {OVER, OVER};
    }
    if(diff1 > diff2) {
        return data2;
    }
    if(diff1 == diff2) {
        return {EQUAL, EQUAL};
    }
    if(diff1 < diff2) {
        return data1;
    }
    return {DEFAULT, DEFAULT};
}

void create() {
    ll key, value;
    cin >> key >> value;

    database.insert({key,value});
}
void modify() {
    ll key, value;
    cin >> key >> value;

    pll close_data = find_close_data_key(key);
    if(close_data.first == OVER) {
        return;
    }
    if(close_data.first == EQUAL) {
        return;
    }
    database.erase(close_data);
    database.insert({close_data.first, value});
}
void print() {
    ll key;
    cin >> key;

    pll close_data = find_close_data_key(key);
    if(close_data.first == OVER) {
        cout << "-1\n";
        return;
    }
    if(close_data.first == EQUAL) {
        cout << "?\n";
        return;
    }
    cout << close_data.second << "\n";

}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> m >> k;

    for(ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        database.insert({x,y});
    }

    while(m--) {
        ll command;
        cin >> command;

        switch(command) {
            case 1: 
                create();
                break;
            case 2:
                modify();
                break;
            case 3:
                print();
                break;
        }
    }

    return 0;
}
