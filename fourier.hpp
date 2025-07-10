#pragma once

#include <utility>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <cstdio>
#include <cassert>

using namespace std;
using T = double;
using ULL = unsigned long long;

string int_to_str(ULL x, int n) {
    string s(n, '0');
    for (ULL i = 0; i < n; ++i)
        s[i] = ((x >> i) & 1) ? '1' : '0';
    return s;
}


struct Fourier {
    vector<T> coeffs;
    int n;
    ULL nn = 1ULL << n;
    string name;

    static int chi(ULL s, ULL x, int n) {
        int result = 0;
        for (int i = 0; i < n; ++i)
            result += ((s >> i) & 1ULL) * ((x >> i) & 1ULL);
        return (result % 2 == 0 ? 1 : -1);
    }

    // Convert from {0,1} to {-1,1}
    static T from_bin_to_pm1(bool x) {
        return x ? -1.0 : 1.0;
    }

    // Convert from {-1,1} to {0,1}
    static bool from_pm1_to_bin(T x) {
        return x < 0;
    }

    Fourier(const vector<bool> &truth_table, int n, string name = "")
            : n(n), nn(1Ull << n), coeffs(1Ull << n), name(std::move(name)) {
        if (truth_table.size() != (1Ull << n)) {
            throw invalid_argument("Длина таблицы истинности должна быть равна 2^n");
        }
        for (ULL s = 0; s < nn; ++s) {
            T coeff = 0.0;
            for (ULL x = 0; x < nn; ++x)
                coeff += chi(s, x, n) * from_bin_to_pm1(truth_table[x]); // -1, 1
//                coeff += chi(s, x, n) * truth_table[x]; // 0, 1
            coeff /= T(nn);
            coeffs[s] = coeff;
        }
    }

    [[nodiscard]] T evaluate_fourier(ULL x) const {
        T result = 0.0;
        for (ULL i = 0; i < nn; ++i)
            result += coeffs[i] * chi(i, x, n);
        return result;
    }

    void print_all_values_fourier() const {
        printf("Значения функции %s в точках:\n", name.c_str());

        for (ULL x = 0; x < nn; ++x) {
            double value = evaluate_fourier(x);
            printf("%s(%s) = %.4f   Fourier: %.4f\n",
                   name.c_str(), int_to_str(x, n).c_str(), value, coeffs[x]);
        }
    }

    [[nodiscard]] T measure() const {
        vector <T> influences(n, 0);
        for (ULL i = 0; i < nn; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1)
                    influences[j] += coeffs[i] * coeffs[i];
            }
        }
        T norm = 0;
        for (int j = 0; j < n; ++j)
            norm += influences[j] * influences[j];
        if (norm == 0)
            return 0;
        T m = 0;
        for (int j = 0; j < n; ++j) {
            m += influences[j] / sqrt(norm);
        }
        return m * m * energy();
    }

    [[nodiscard]] T energy() const {
        T result = 0;
        for (ULL i = 0; i < nn; ++i)
            result += coeffs[i] * coeffs[i] * __builtin_popcount(i);
        return result;
    }

    void print_measure() const {
        printf("Мера функции %s: %.4f\n", name.c_str(), measure());
    }

    Fourier MUL(const Fourier &g) const {
        if (n != g.n)
            throw invalid_argument("Функции должны иметь одинаковую размерность");
        vector<bool> truth_table(nn);
        for (ULL x = 0; x < nn; ++x)
            truth_table[x] = from_pm1_to_bin(evaluate_fourier(x) * g.evaluate_fourier(x));

        return Fourier(truth_table, n, "(" + name + " * " + g.name + ")");
    }

    Fourier CONV(const Fourier &g) const {
        if (n != g.n)
            throw invalid_argument("Функции должны иметь одинаковую размерность");
        Fourier result = *this;
        for (ULL i = 0; i < nn; ++i)
            result.coeffs[i] *= g.coeffs[i];
        result.name = "(" + name + " ⊗ " + g.name + ")";
        return result;
    }

    Fourier AND(const Fourier &g) const {
        if (n != g.n)
            throw invalid_argument("Функции должны иметь одинаковую размерность");
        vector<bool> truth_table(nn);
        for (ULL x = 0; x < nn; ++x) {
            T value_f = evaluate_fourier(x);
            T value_g = g.evaluate_fourier(x);
//            truth_table[x] = value_f * value_g; // 0, 1
            truth_table[x] = from_pm1_to_bin((1.0 + value_f + value_g - value_f * value_g) / 2.0); // -1, 1
        }
        return Fourier(truth_table, n, "(" + name + " ∧ " + g.name + ")");
    }

    Fourier OR(const Fourier &g) const {
        if (n != g.n)
            throw invalid_argument("Функции должны иметь одинаковую размерность");
        vector<bool> truth_table(nn);
        for (ULL x = 0; x < nn; ++x) {
            T value_f = evaluate_fourier(x);
            T value_g = g.evaluate_fourier(x);
//            truth_table[x] = value_f + value_g - value_f * value_g; // 0, 1
            truth_table[x] = from_pm1_to_bin((-1.0 + value_f + value_g + value_f * value_g) / 2.0); // -1, 1
        }
        return Fourier(truth_table, n, "(" + name + " ∨ " + g.name + ")");
    }

    Fourier XOR(const Fourier &g) const {
        if (n != g.n)
            throw invalid_argument("Функции должны иметь одинаковую размерность");
        vector<bool> truth_table(nn);
        for (ULL x = 0; x < nn; ++x) {
            T value_f = evaluate_fourier(x);
            T value_g = g.evaluate_fourier(x);
            truth_table[x] = value_f * value_g; // -1, 1
//            truth_table[x] = value_f + value_g - 2 * value_f * value_g; // 0, 1
        }
        return Fourier(truth_table, n, "(" + name + " ⊕ " + g.name + ")");
    }
};
