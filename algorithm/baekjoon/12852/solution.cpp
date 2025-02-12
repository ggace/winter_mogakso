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

ll n;
ll counts[1010101];
ll backtrack[1010101];
vector<ll> result;


void calc_min() {
    fill_n(counts, 1010101, LONG_LONG_MAX);

    queue<pll> q; // number, count

    q.push({n, 0});
    backtrack[n] = -1;
    counts[n] = 0;

    while(!q.empty()) {
        auto [cur_num, cur_count] = q.front();
        q.pop();
        // debug(cur_num << " " << cur_count);

        if(counts[cur_num] < cur_count){ 
            // debug("continue");
            continue;
        }
        if(cur_num == 1) {
            break;
        }

        if(cur_num % 2 == 0) {
            if(cur_count +1 < counts[cur_num/2]){
                q.push({cur_num/2, cur_count+1});
                counts[cur_num/2] = cur_count+1;
                backtrack[cur_num/2] = cur_num;
            }
        }
        if(cur_num % 3 == 0) {
            if(cur_count +1 < counts[cur_num/3]){
                q.push({cur_num/3, cur_count+1});

                counts[cur_num/3] = cur_count+1;
                backtrack[cur_num/3] = cur_num;
            }
        }
        
        if(cur_count +1 < counts[cur_num-1]){
            q.push({cur_num-1, cur_count+1});
            counts[cur_num-1] = cur_count+1;
            backtrack[cur_num-1] = cur_num;
        }
    }

    
    for(ll i = 1; i != -1; i = backtrack[i]) {
        result.push_back(i);
    }
    
    cout << counts[1] << "\n";
    for(int i = result.size()-1; i >= 0; i--) {
        cout << result[i] << " ";
    }
    cout << "\n";
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n;

    calc_min();
    
    return 0;
}
