# 12757
- [문제 페이지](https://boj.kr/12757)

## 1) 문제 설명

데이터베이스엔 특정 key에 value가 들어있다. 이때, key가 정확히 맞지 않더라도 입력된 key와 실제 key의 차이가 k 이하일 경우 이 key에 들어있는 value를 접근하도록 한다.

1 key value가 들어올 경우, database에 key에 value를 삽입한다. (이미 key에 value가 들어있는 경우는 없다.)

2 key value가 들어올 경우, 입력된 key와 database의 key가 가장 가까운 key의 value를 입력된 value로 수정한다.

3 key가 들어올 경우, 입력된 key와 database의 key가 가장 가까운 key의 value를 출력한다.

## 2) 문제 해설
1 key value가 들어올 경우
- 저장된 database의 key에 value를 저장한다.

입력된 key와 가장 가까운 key를 찾아야 한다. 이때, 입력된 key를 database에 대해 lowerbound 할 경우, 이는 항상 key와 같거나 크다. 또한, 이보다 한 인덱스 작은 경우, 이는 항상 key와 같거나 작다.

두 키를 입력된 key와 비교해 두 key 모두 key보다 클 경우 -2, 두 key의 차이가 같을 경우 -1, 오류 발생시 -3을 index로 하며, 이외의 경우 database의 {key, value}를 출력하는 함수를 만든다. 

이를 이용해, key값을 얻어 이를 변조 및 출력할 수 있도록 할 수 있다.

## 3) 코드
```c
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
```

