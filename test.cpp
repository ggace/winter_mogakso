#include <bits/stdc++.h>

using ll = long long;
using namespace std;
ll N;

int main() {
    
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            bool is_print = false;
            for(int k = N; k >= 1; k /= 3) {
                if((i %(3*k))/ k == 1 && (j %(3*k)) / k == 1) {
                    cout << " ";
                    is_print = true;
                    break;
                }
            }
            if(!is_print) {
                cout << "*";
            }
        }
        cout << "\n";
    }
}