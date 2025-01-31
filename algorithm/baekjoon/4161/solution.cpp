typedef long long ll;

#define fio cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(false);

#include <bits/stdc++.h>

using namespace std;

ll f(ll a, ll b, ll x, ll y, ll t) {
    ll result = 0;
    result += abs((2*a + b + 4*t) / 3 + 3*x + 4*y);
    result += abs((a + 2*b + 5*t) / 3 + 3*x + 5*y);
    result += abs(x);
    result += abs(x + 3*y + t);

    return result;
}

void solution(ll a, ll b) {
    ll t = (a + 2*b) % 3;

    vector<array<ll, 2>> points = {
        {(b - 2*a)/3    ,  (a - b - t)/3},
        {0              , -(2*a + b + 4*t)/12},
        {-(2*a + b)/5   ,  (2*a + b - 5*t)/15},
        {0              , -(a + 2*b + 5*t)/15},
        {-(a + 2*b)/4   ,  (a + 2*b - 5*t)/12},
        {0              , -t/3}
    };

    ll result = LONG_LONG_MAX;

    for(int i = 0; i < 6; i++) {
        for(ll dx = -2; dx <= 2; dx++) {
            for(ll dy = -2; dy <= 2; dy++) {
                result = min(result, f(a, b, points[i][0] + dx, points[i][1] + dy, t));
            }
        }
    }
    cout << result << "\n";
}

int main(int argc, char* argv[]) {
    fio;

    while(true){

        string s;
        getline(cin, s); // 한 줄 입력받기

        if(s.compare("END") == 0) {
            break;
        }
        ll a, b;
        stringstream ss(s);
        ss >> a >> b;

        solution(a, b);
    }

    return 0;
}
