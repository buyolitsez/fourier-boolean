//#include "fourier.hpp"
//#include "check_xor_dnf.h"
#include "check_all_functions.h"

Fourier or_from_subset(int subset, int n) {
    vector<bool> truth_table(1ll << n, 1);
    truth_table[subset] = 0;
    return Fourier(truth_table, n, "or_" + to_string(subset));
}

vector<Fourier> generate_all_functions(int n) {
    vector<Fourier> functions;
    ULL function_size = 1ULL << n;
    ULL num_functions = 1ULL << (function_size);

    for (size_t i = 0; i < num_functions; ++i) {
        vector<bool> function(function_size);
        for (size_t j = 0; j < function_size; ++j) {
            function[j] = ((i >> j) & 1);
        }
        functions.emplace_back(function, n, to_string(i));
    }
    return functions;
}

int main() {
    Fourier f({0, 1, 1, 0, 1, 0, 0, 1}, 3, "f");
//    Fourier f({0, 1, 0, 1, 0, 1, 0, 1}, 3, "f");
    f.print_all_values_fourier();
    f.print_measure();
    int n = 3;
    check_all_functions(n, 2, generate_all_functions(n));
//    Fourier x1({0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 4, "x1");
//    Fourier x2({0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1}, 4, "x2");
//    Fourier x3({0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1}, 4, "x3");
//    Fourier x4({0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}, 4, "x4");
//    Fourier f = x1.XOR(x2);
//    f.print_all_values_fourier();
//    f.print_measure();
//    Fourier g = x3.XOR(x4);
//    g.print_measure();
//    f.AND(g).print_measure();
    return 0;
}
