#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <cstdio>

using namespace std;

string int_to_str(int x, int n) {
    string s(n, '0');
    for (int i = 0; i < n; ++i)
        s[i] = ((x >> i) & 1) ? '1' : '0';
    return s;
}

using T = double;

struct Fourier {
    vector<T> coeffs;
    int n;
    int nn = 1 << n;
};

int chi(int s, int x, int n) {
    int result = 0;
    for (int i = 0; i < n; ++i)
        result += ((s >> i) & 1) * ((x >> i) & 1);
    return (result % 2 == 0 ? 1 : -1);
}

Fourier fourier_decomposition(const vector<int>& truth_table, int n) {
    if (truth_table.size() != (1ll << n)) {
        throw invalid_argument("Длина таблицы истинности должна быть равна 2^n");
    }
    vector<T> result(1ll << n);
    for (int s = 0; s < (1 << n); ++s) {
        T coeff = 0.0;
        for (int x = 0; x < (1ll << n); ++x)
            coeff += chi(s, x, n) * (truth_table[x] ? -1 : 1);
        coeff /= (1ll << n);
        result[s] = coeff;
    }
    return Fourier{result, n};
}

T evaluate_fourier(const Fourier& f, int x) {
    T result = 0.0;
    for (int i = 0; i < f.nn; ++i)
        result += f.coeffs[i] * chi(i, x, f.n);
    return result;
}

void print_all_values_fourier(const Fourier& f, const string& name = "") {
    printf("Значения функции %s в точках:\n", name.c_str());
    
    for (int x = 0; x < f.nn; ++x) {
        double value = evaluate_fourier(f, x);
        printf("%s(%s) = %.4f   Fourier: %.4f\n", 
            name.c_str(), int_to_str(x, f.n).c_str(), value, f.coeffs[x]);
    }
}