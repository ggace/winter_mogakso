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

ll n, m;
vector<vector<array<ll, 2>>> edges(2020); // to, weight, number
bool visited[2020];

ll edges_count[5050];
ll track[5050];
ll weights[5050];

map<array<ll, 2>, ll> edge_number;
map<ll, vector<ll>> count_sort;

vector<vector<ll>> backtrack_tree(2020);
bool backtrack_visited[2020];

ll dfs(ll before, ll start) {
    // debug(start);
    // cout << before << " " << start << "\n";

    if(backtrack_tree[start].size() == 0) {
        ++edges_count[edge_number[{before, start}]];

        // cout << edge_number[{before, start}] << ": " << 1 << "\n\n";
        return 1;
    }

    ll temp = 1;
    for(auto next : backtrack_tree[start]) {
        
        if(backtrack_visited[next]) {
            continue;
        }
        backtrack_visited[next] = true;
        temp += dfs(start, next);
    }
    // cout << edge_number[{before, start}] << ": " << temp << "\n\n";
    if(before)
        edges_count[edge_number[{before, start}]] += temp;
    return temp;
}

void djikstra(ll start) {
    memset(track, 0, sizeof(track));
    fill_n(weights, 5050, LONG_LONG_MAX);
    memset(backtrack_visited, 0, sizeof(backtrack_visited));
    memset(visited, 0, sizeof(visited));

    for(ll i = 0; i <= n; i++) {
        backtrack_tree[i].clear();
    }

    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq; // -weight, cur, used_edge

    pq.push({0, start});
    weights[start] = 0;

    while(!pq.empty()) {
        auto [cur_weight, cur_index] = pq.top();
        pq.pop();

        if(weights[cur_index]!=cur_weight) continue;
        for(auto [next, next_weight] : edges[cur_index]) {
            if(weights[next] <= weights[cur_index] + next_weight) {
                continue;
            }
            weights[next] = weights[cur_index] + next_weight;
            track[next] = cur_index;
            pq.push({weights[cur_index]+next_weight, next});
        }
    }

    for(ll i = 1; i <= n; i++) {
        if(!track[i] || visited[i]) continue;
        
        for(ll j = i; j != start && !visited[j]; j = track[j]) {
            backtrack_tree[track[j]].push_back(j);
            visited[j] = true;
        }
    }

    dfs(0, start);
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> m;

    for(int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        edges[a].push_back({b, c});
        edge_number[{a, b}] = i+1;
    }

    for(int i = 1; i <= n; i++) {
        debug(i);
        djikstra(i);
    }

    ll max_value = LONG_LONG_MIN;
    for(int i = 1; i <= m; i++) {
        debug(i << ": " << edges_count[i]);
        count_sort[edges_count[i]].push_back(i);

        max_value = max(max_value, edges_count[i]);
    }

    sort(count_sort[max_value].begin(), count_sort[max_value].end());

    cout << count_sort[max_value].size() << "\n";

    for(auto index : count_sort[max_value]) {
        cout << index << " ";
    }
    cout << "\n";

    return 0;
}
