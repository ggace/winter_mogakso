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

ll fastpow(ll a, ll n, ll c){
    ll result=1;
    while(n){
        if(n&1){
            result *=a;
            if(result>=c) result%=c;
        }
        a*=a;
        if(a>=c) a%=c;
        n>>=1;
    }
    return result;
}

vector<ll> prime_list;
bool is_prime[PRIME_SIZE+1] = {1,1,0}; // 0이 소수
void siv(ll n) {
    for(int i = 2; i <= n; i++) {
        if(!is_prime[i]) prime_list.push_back(i);
        for(auto p : prime_list) {
            if(i*p > n) break;
            is_prime[i*p] = true;
            if(i%p == 0) break;
        }
    }
}

ll n, m;
vector<vector<array<ll, 3>>> edges(2020); // to, weight, number
ll edges_count[5050];
ll track[5050];
ll visited[2020];

vector<vector<ll>> count_sort(5050);

void djikstra(ll start) {
    memset(track, -1, sizeof(track));
    memset(visited, 0, sizeof(visited));

    priority_queue<array<ll, 3>> pq; // -weight, cur, used_edge

    pq.push({0, start, 0});

    while(!pq.empty()) {
        auto [cur_weight, cur_index, used_edge] = pq.top();
        cur_weight = -cur_weight;
        pq.pop();

        if(visited[cur_index]) {
            continue;
        }
        visited[cur_index] = true;

        for(auto [next, next_weight, next_number] : edges[cur_index]) {
            if(visited[next]) {
                continue;
            }
            track[next_number] = used_edge;
            pq.push({-cur_weight-next_weight, next, next_number});
        }
    }

    for(ll i = 1; i <= m; i++) {
        if(track[i] == -1) {
            continue;
        }
        // ll t = 1;
        for(ll j = i; j != 0;) {
            cout << j << " -> ";
            edges_count[j]++;
            j = track[j];
            // t++;
        }
        cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> m;

    for(int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        edges[a].push_back({b, c, i+1});
    }

    for(int i = 1; i <= n; i++) {
        debug(i);
        djikstra(i);
    }

    ll max_value = LONG_LONG_MIN;
    for(int i = 1; i <= m; i++) {
        debug(i << ": " << edges_count[i]);
        count_sort[edges_count[i]].push_back(i);
        if(max_value < edges_count[i]) {
            max_value = edges_count[i];
        }
    }

    cout << count_sort[max_value].size() << "\n";

    for(auto index : count_sort[max_value]) {
        cout << index << " ";
    }
    cout << "\n";

    return 0;
}
