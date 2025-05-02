#include <utility>
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

int chi(int s, int x, int n) {
    int result = 0;
    for (int i = 0; i < n; ++i)
        result += ((s >> i) & 1) * ((x >> i) & 1);
    return (result % 2 == 0 ? 1 : -1);
}

struct Fourier {
    vector<T> coeffs;
    int n;
    int nn = 1 << n;
    string name;

    Fourier(const vector<bool>& truth_table, int n, string  name = "")
        : n(n), nn(1ll << n), coeffs(1ll << n), name(std::move(name)) {
        if (truth_table.size() != (1ll << n)) {
            throw invalid_argument("Длина таблицы истинности должна быть равна 2^n");
        }
        for (int s = 0; s < (1 << n); ++s) {
            T coeff = 0.0;
            for (int x = 0; x < (1ll << n); ++x)
                coeff += chi(s, x, n) * (truth_table[x] ? -1 : 1);
            coeff /= T(1ll << n);
            coeffs[s] = coeff;
        }
    }

    T evaluate_fourier(int x) {
        T result = 0.0;
        for (int i = 0; i < nn; ++i)
            result += coeffs[i] * chi(i, x, n);
        return result;
    }

    void print_all_values_fourier() {
        printf("Значения функции %s в точках:\n", name.c_str());

        for (int x = 0; x < nn; ++x) {
            double value = evaluate_fourier(x);
            printf("%s(%s) = %.4f   Fourier: %.4f\n",
                   name.c_str(), int_to_str(x, n).c_str(), value, coeffs[x]);
        }
    }

    T energy() {
        T result = 0;
        for (int i = 0; i < nn; ++i)
            result += coeffs[i] * coeffs[i] * __builtin_popcount(i);
        return result;
    }
    void print_energy() {
        printf("Энергия функции %s: %.4f\n", name.c_str(), energy());
    }
};
