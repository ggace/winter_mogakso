# 18870
- [문제페이지](https://boj.kr/18870)

## 1) 문제 설명
좌표압축문제이다. 

## 2) 문제 풀이
벡터에 값을 저장하고, 또 다른 벡터를 만들어 저장한다. 이후 lower_bound를 통해 앞에 있는 값의 개수를 출력하면 된다.

## 3) 코드
```cpp
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

```