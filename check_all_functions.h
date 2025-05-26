#pragma once

#include "fourier.hpp"
#include <vector>

using namespace std;

void check_all_functions(int n) {
    // Number of possible functions is 2^(2^n)
    ULL function_size = 1ULL << n;
    ULL num_functions = 1ULL << (function_size);
    vector<Fourier> functions;

    // Generate all possible functions
    for (size_t i = 0; i < num_functions; ++i) {
        vector<bool> function(function_size);
        for (size_t j = 0; j < function_size; ++j) {
            function[j] = ((i >> j) & 1);
        }
        functions.emplace_back(function, n, to_string(i));
    }

    T mx = 1;
    ULL skipped = 0;
    // Iterate through all pairs of functions
    for (ULL i = 0; i < functions.size(); ++i) {
        printf("i = %llu\n", i);
        T mi = functions[i].measure();
        for (size_t j = i + 1; j < functions.size(); ++j) {
            T mj = functions[j].measure();
            Fourier h = functions[i].AND(functions[j]);
            T mh = h.measure();
            if (mx * max(mi, mj) < mh) {
                mx = mh / max(mi, mj);
                printf("i = %llu, mx = %.8f\n", i, mx);
//                printf("Нашел!\n");
//                printf("f = %s\n", functions[i].name.c_str());
//                functions[i].print_all_values_fourier();
//                functions[i].print_measure();
//                printf("g = %s\n", functions[j].name.c_str());
//                functions[j].print_all_values_fourier();
//                functions[j].print_measure();
//                printf("h = %s\n", h.name.c_str());
//                h.print_all_values_fourier();
//                h.print_measure();
//                return;
            }
        }
    }
    printf("END\n");
    printf("final mx = %.8f\n", mx);
}