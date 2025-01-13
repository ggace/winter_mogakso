typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define PRIME_SIZE 5
#define PIE M_PIf64

#define BOJ

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

enum CONSTANT {
    INVALID = LONG_LONG_MIN
};

vector<ll> segtree;
ll seg_depth;

ll fastpow(ll a, ll n){
    ll result=1;
    while(n){
        if(n&1){
            result *=a;
        }
        a*=a;
        n>>=1;
    }
    return result;
}

void resize(ll size) {
    ll depth = ceil(log2(size));
    segtree.resize(fastpow(2, depth+1));
    seg_depth = depth;
}

void update_value(ll index, ll value) {
    ll real_index = fastpow(2, seg_depth) + index;
    if(real_index >= segtree.size()) {
        return;
    }
    ll cur_value = segtree[real_index];
    ll value_change = value - cur_value;
    while(true) {
        segtree[real_index] += value_change;
        if(real_index == 1) {
            break;
        }
        real_index /= 2;
    }
}

ll get_value(ll start, ll end) {
    ll prev_index = fastpow(2, seg_depth);
    start = prev_index + start;
    end = prev_index + end;

    ll result = 0;

    ll index = 1;
    queue<pll> q;
    q.push({index, 0});
    while(!q.empty()) {
        auto [cur_index, cur_depth] = q.front();
        q.pop();
        debug(cur_index << " " << cur_depth);

        ll possible_range = fastpow(2, seg_depth - cur_depth);

        ll left = cur_index * possible_range;
        ll right = (cur_index + 1) * possible_range - 1;

        debug(left << " <-> " << right);

        if(start <= left && right <= end) {
            debug("possible at " << cur_index);
            result += segtree[cur_index];
            continue;
        }
        if(end < left) {
            continue;
        }
        if(start > right) {
            continue;
        }
        ll next_index = cur_index * 2;
        if(next_index >= segtree.size()) {
            continue;
        }
        
        q.push({next_index, cur_depth+1});
        q.push({next_index+1, cur_depth+1});

    }
    

    return result;
}

ll n, m, k;

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> m >> k;

    resize(n);
    for(ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        update_value(i, x);
    }

    for(ll i = 0; i < m + k; i++) {
        ll a, b, c; cin >> a >> b >> c;

        switch(a) {
            case 1:
                update_value(b-1, c);
                break;
            case 2:
                cout << get_value(b-1,c-1) << "\n";
                break;
        }
    }
    
        

    return 0;
}
