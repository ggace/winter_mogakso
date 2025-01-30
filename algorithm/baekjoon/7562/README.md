# 7562
- [문제페이지](https://boj.kr/7562)

## 1) 문제설명
i * i 크기를 가진 체스판이 있을때, (0,0)에서 시작한 나이트가 (x, y)로 이동하기 위해 이동해야하는 최소 횟수를 출력하는 문제이다.

## 2) 문제풀이
기본 bfs문제이다. 크기를 정한 공간 내에서 횟수를 구해가며 해당 지점에 도착했다면, 그 값을 출력하면 된다.

## 3) 코드
```c
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

#define pii pair<int, int>
#define pll pair<ll, ll>
#define PRIME_SIZE 5
#define PIE M_PIf64

// #define BOJ

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

ll direc[8][2] = {
    {1,2},
    {1,-2},
    {2,1},
    {2,-1},
    {-1,2},
    {-1,-2},
    {-2,1},
    {-2,-1}
};

void solution() {
    ll l; 
    ll x_initial, y_initial, x_final, y_final;
    ll delta_x, delta_y;

    queue<array<ll, 3>> q;
    ull result[303][303];

    memset(result, -1, sizeof(result));

    cin >> l;
    cin >> x_initial >> y_initial >> x_final >> y_final;

    debug(l << ": ");

    q.push({x_initial, y_initial, 0});

    while(!q.empty()) {
        auto [cur_x, cur_y, cur_cnt] = q.front();
        q.pop();

        if(cur_x == x_final && cur_y == y_final) {
            cout << cur_cnt << "\n";
            break;
        }

        for(int i = 0; i < 8; i++) {
            ll next_x = cur_x + direc[i][0];
            ll next_y = cur_y + direc[i][1];

            if(next_x < 0 || next_x > l-1 || next_y < 0 || next_y > l-1) {
                continue;
            }
            
            if(result[next_x][next_y] > cur_cnt+1) {
                q.push({next_x, next_y, cur_cnt+1});
                result[next_x][next_y] = cur_cnt+1;
            }
            
        }
    }


}

int main(int argc, char* argv[]) {
    fio; 

    ll t; cin >> t;

    while(t--) {
        solution();
    }

    return 0;
}

```
