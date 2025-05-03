#pragma once

#include "fourier.hpp"
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

vector<int> generate_even_subsets(int n) {
    vector<int> result;
    for (int bits = 0; bits < (1ll << n); ++bits) {
        if (__builtin_popcount(bits) % 2 == 0) {
            result.emplace_back(bits);
        }
    }
    return result;
}

Fourier build_and(const vector<int>& even_subsets, int l, int r, int n, int depth = 0) {
    if (l == r) {
        // OR of the subset
        vector<bool> truth_table(1ll << n, 1);
        truth_table[even_subsets[l]] = 0;
        Fourier f(truth_table, n, to_string(l));
        return f;
    } else {
        int m = l + (r - l) / 2;
        Fourier f1 = build_and(even_subsets, l, m, n, depth + 1);
        Fourier f2 = build_and(even_subsets, m + 1, r, n, depth + 1);
        
        Fourier h = f1.AND(f2);
        if (l == 0) {
            T energy1 = f1.measure();
            T energy2 = f2.measure();
            T energy = h.measure();
            printf("Изменение меры при l=%d, r=%d: %.8f, %.8f -> %.8f, (want %.8f)\n", l, r, energy1, energy2, energy, (energy1 + energy2) / sqrt(2.0));
        }
        return h;
    }
}

void check_xor_16_dnf() {
    const int n = 8;
    vector<int> even_subsets = generate_even_subsets(n);
    build_and(even_subsets, 0, even_subsets.size() - 1, n);
}
