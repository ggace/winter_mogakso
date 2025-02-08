#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <iomanip>
#include <numeric>

using namespace std;
using Complex = complex<double>;

vector<double> get_data(int T, int Fs) {
    vector<double> x, y;
    for (int i = 0; i < T * Fs; i++) {
        x.push_back(i / static_cast<double>(Fs));
    }
    for (double i : x) {
        y.push_back(0.7 * sin(2 * M_PI * 10 * i) + sin(2 * M_PI * 150 * i) + sin(2 * M_PI * 50 * i));
    }
    return y;
}

vector<double> preprocess_data(const vector<double>& data, int T, int Fs) {
    vector<double> y = data;
    int sample_capacity = pow(2, ceil(log2(T * Fs)));
    y.resize(sample_capacity, 0);
    double avg_y = accumulate(y.begin(), y.end(), 0.0) / y.size();
    for (double& val : y) {
        val -= avg_y;
    }
    return y;
}

vector<Complex> bit_reverse_copy(const vector<Complex>& x) {
    int n = 1, log_n = 0;
    while (n < x.size()) {
        n <<= 1;
        log_n++;
    }
    vector<Complex> matrix(n);
    for (int i = 0; i < n; i++) {
        int temp = 0;
        int binary = 1;
        int reverse_binary = n >> 1;
        for (int j = 0; j < log_n; j++) {
            if (i & binary) {
                temp |= reverse_binary;
            }
            reverse_binary >>= 1;
            binary <<= 1;
        }
        matrix[i] = x[temp];
    }
    return matrix;
}

vector<Complex> fft(vector<double> x) {
    vector<Complex> C_m(x.begin(), x.end());
    C_m = bit_reverse_copy(C_m);
    int size = C_m.size();
    for (int i = 2; i <= size; i <<= 1) {
        for (int t = 0; t < size / i; t++) {
            for (int j = 0; j < i / 2; j++) {
                double theta = -2 * M_PI * j / i;
                Complex Wk = Complex(cos(theta), sin(theta));
                int front_index = j + i * t;
                int back_index = j + i / 2 + i * t;
                Complex front = C_m[front_index];
                Complex back = C_m[back_index];
                C_m[front_index] = front + Wk * back;
                C_m[back_index] = front - Wk * back;
            }
        }
    }
    return C_m;
}

int main() {
    int t = 2;
    int Fs = 1000000;
    vector<double> y = preprocess_data(get_data(t, Fs), t, Fs);

    cout << "\n=======================" << endl;
    cout << " ______ ______ _______ " << endl;
    cout << "|  ____|  ____|__   __|" << endl;
    cout << "| |__  | |__     | |   " << endl;
    cout << "|  __| |  __|    | |   " << endl;
    cout << "| |    | |       | |   " << endl;
    cout << "|_|    |_|       |_|   " << endl;
    cout << "=======================\n" << endl;
    
    cout << "Please, write the number if you want to see graph" << endl;
    cout << "1. show graph" << endl;
    cout << "2. skip showing graph" << endl;
    
    int is_show_graph;
    cin >> is_show_graph;
    bool show_graph = (is_show_graph == 1);
    
    cout << "\nProcessing FFT...\n";
    vector<Complex> result = fft(y);
    
    vector<double> f_list, fft_result;
    
    cout << "\n";
    cout << "-------------------------------------------------------" << endl;
    cout << "| " << setw(15) << "f" << " | " << setw(15) << "value" << " | " << setw(15) << "lambda" << " |" << endl;
    cout << "-------------------------------------------------------" << endl;
    
    for (size_t i = 0; i < result.size(); i++) {
        double value = abs(result[i]) / y.size();
        double f = i * Fs / y.size();
        if (value > 0.3) {
            cout << "| " << setw(15) << f << " | " << setw(15) << value << " | " << setw(15) << (f != 0 ? 1 / f : INFINITY) << " |" << endl;
        }
        f_list.push_back(f);
        fft_result.push_back(value);
    }
    
    cout << "-------------------------------------------------------" << endl;
    
    return 0;
}
