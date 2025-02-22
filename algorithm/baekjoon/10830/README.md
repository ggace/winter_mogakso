# 10830
- [문제페이지](https://boj.kr/10830)

## 1) 문제 설명
행렬 A가 주어질때, $A^b$ 를구하면 된다.

## 2) 문제 풀이 
분할정복을 사용하여 거듭제곱을 계산하면 된다.

## 3) 코드
```cpp
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

ll n, b;

vector<vector<ll>> v(8, vector<ll>(8));

vector<vector<ll>> multiply_matrix(vector<vector<ll>> A, vector<vector<ll>> B) {
    vector<vector<ll>> result_matrix(8, vector<ll>(8, 0));
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            for(ll k = 0; k < n; k++) {
                result_matrix[i][j] += A[i][k] * B[k][j];
                result_matrix[i][j] %= 1000;
            }
        }
    }
    return result_matrix;
}

vector<vector<ll>> pow_matrix() {
    vector<vector<ll>> result_matrix = {
        {1,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0},
        {0,0,0,0,1,0,0,0},
        {0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,1},
    };
    for(ll i = 1l; i <= b; i <<= 1) {
        if(b & i) {
            debug(i);
            result_matrix = multiply_matrix(result_matrix, v);
        }
        v = multiply_matrix(v, v);
    }
    return result_matrix;
}

int main(int argc, char* argv[]) {
    fio; 

    cin >> n >> b;

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    auto result = pow_matrix();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << result[i][j] << " ";
        }
        cout << "\n";
    }



    return 0;
}

```