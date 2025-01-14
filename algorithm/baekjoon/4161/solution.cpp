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
#define debug(x)  cout << "[Debug] " << x;
#define debug_value(x)  cout << "[Debug] " << #x << " is " << x << '\n';
#define fio ((void)0);
#endif

#include <bits/stdc++.h>

using namespace std;

struct Direction {
    ll dx;
    ll dy;
};

struct Position {
    ll x;
    ll y;
};

ll fastpow_with_modular(ll a, ll n, ll c){
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

vector<vector<array<ll, 4>>> chess_board(33, vector<array<ll, 4>>(33));
array<array<bool, 33>, 33> visited;

int direc[10][2] = {
    {1,2},
    {-1, -2},
    {-2, -1},
    {2, 1},
    {2, -1},
    {-2, 1},
    {-1, 2},
    {1, -2}
};

void preset() {
    int x = 16, y = 16;
    
    queue<array<int, 3>> q;

    q.push({x,y,1});
    chess_board[16][16] = {0,0,0,0};
    visited[16][16] = true;
    

    for(int i = 0; true; i++) {
        auto [cur_x, cur_y, count] = q.front();

        // cout << cur_x << " " << cur_y << "\n";

        if(count == 9) {
            break;
        }
        q.pop();

        for(int j = 0; j < 8; j++) {
            int next_x = cur_x + direc[j][0];
            int next_y = cur_y + direc[j][1];
            if(!visited[next_x][next_y]) {
                q.push({next_x, next_y, count+1});
                visited[next_x][next_y] = true;
                chess_board[next_x][next_y] = chess_board[cur_x][cur_y];
                if(j %2)
                    --chess_board[next_x][next_y][j/2];
                else 
                    ++chess_board[next_x][next_y][j/2];
                // cout << (next_x-16) << " " << (next_y-16) << ": " << chess_board[next_x][next_y][0] << " " << chess_board[next_x][next_y][1] << " " << chess_board[next_x][next_y][2] << " " << chess_board[next_x][next_y][3] << "\n";
            }
        }
    }

    chess_board[16][16][0] = 0;
}

ll f(array<ll, 4> result, ll t) {
    return abs(result[0] - 3*t) + abs(result[1] - 3*t) + abs(result[2] - t) + abs(result[3] + t);
}

int main(int argc, char* argv[]) {
    fio; 

    preset();

    while(true){
        

        string s;
        getline(cin, s); // 한 줄 입력받기

        if(s.compare("END") == 0) {
            break;
        }
        ll x, y;
        stringstream ss(s);
        ss >> x >> y;

        x = abs(x);
        y = abs(y);
        if(x > y) {
            swap(x, y);
        }

        array<ll, 4> result_matrix;

        ll final_result = LONG_LONG_MAX;
        ll t = (y-x)/2;
        ll k = (y+x)/2;

        result_matrix[0] = t;
        result_matrix[1] = t;
        result_matrix[2] = k;
        result_matrix[3] = k;

        ll a = x +t - k;
        ll b = y -t - k;
        
        debug(t << " " << k << "\n");

        debug(a << " " << b << "\n");

        for(int i = 0; i < 4; i++) {
            debug(result_matrix[i] << " + " << chess_board[a+16][b+16][i] << "\n");
            result_matrix[i] += chess_board[a+16][b+16][i];
        }
        debug("\n");

        ll le = -10'0000'0000, ri = 10'0000'0000;

        while(ri - le >= 3) {
            ll a = (le*2 + ri)/3, b = (le + ri*2)/3;

            if(f(result_matrix, a) <= f(result_matrix, b)) ri = b;
            else le = a;
        }

        ll cur_result = LONG_LONG_MAX;
        for(ll j= le; j <= ri; j++) {

            debug(result_matrix[0] -3*j << "\n");
            debug(result_matrix[1] -3 * j << "\n");
            debug(result_matrix[2] - j << "\n");
            debug(result_matrix[3] + j << "\n");
            debug("\n");
            cur_result= min(cur_result, f(result_matrix, j));
        } 

        

        final_result = min(cur_result, final_result);

        cout << final_result << "\n";
    
    }

    return 0;
}
