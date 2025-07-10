//#include "fourier.hpp"
//#include "check_xor_dnf.h"
#include "check_all_functions.h"

vector<Fourier> generate_or_subsets(int n) {
    vector<Fourier> functions;
    for (ULL subset = 0; subset < (1ULL << n); ++subset) {
        for (ULL submask = subset; ; submask = (submask - 1) & subset) {
            // or of the variables in subset, all in submask with negations
            vector<bool> truth_table(1ULL << n, false);
            for (ULL x = 0; x < (1ULL << n); ++x) {
                for (int i = 0; i < n; ++i) {
                    bool value = ((x >> i) & 1);
                    bool in_subset = ((subset >> i) & 1);
                    bool is_negation = ((submask >> i) & 1);
                    if (in_subset && (value ^ is_negation)) {
                        truth_table[x] = true;
                        break;
                    }
                }
            }

            functions.emplace_back(truth_table, n, "or_" + int_to_str(subset, n) + "_not_" + int_to_str(submask, n));
            if (submask == 0) break;
        }
    }
    return functions;
}

vector<Fourier> generate_all_functions(int n) {
    vector<Fourier> functions;
    ULL function_size = 1ULL << n;
    ULL num_functions = 1ULL << function_size;

    for (ULL i = 0; i < num_functions; ++i) {
        vector<bool> function(function_size);
        for (ULL j = 0; j < function_size; ++j) {
            function[j] = ((i >> j) & 1);
        }
        functions.emplace_back(function, n, to_string(i));
    }
    return functions;
}

Fourier generate_x_i(int n, int i) {
    vector <bool> truth_table(1ULL << n, false);
    for (ULL s = 0; s < (1ULL << n); ++s) {
        bool value = ((s >> i) & 1);
        truth_table[s] = value;
    }
    return Fourier(truth_table, n, "x" + to_string(i));
}

int main() {
//    Fourier f({0, 0, 0, 1}, 2, "and2");
//    Fourier f({0, 1, 1, 0, 1, 0, 0, 1}, 3, "xor3");
//    Fourier x1({0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 5, "x1");
//    Fourier x2({0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1}, 5, "x2");
//    Fourier f = x1.AND(x2);
//    f.print_all_values_fourier();
//    f.print_measure();
    int n = 4;
//    return 0;
    vector <Fourier> functions = generate_or_subsets(n);
    printf("Total functions: %llu\n", functions.size());
    check_all_functions(n, 2, functions);

return 0;
//    Fourier f1 = generate_x_i(n, 0);
//    Fourier f2 = generate_x_i(n, 1);
//    for (int i = 2; i < n; ++i) {
//        if (i % 2 == 0)
//            f1 = f1.OR(generate_x_i(n, i));
//        else
//            f2 = f2.OR(generate_x_i(n, i));
//    }

    Fourier f1 = functions[127];
    Fourier f2 = functions[43688];
    f1.print_all_values_fourier();
    f1.print_measure();
    printf("energy = %f\n", f1.energy());
    f2.print_all_values_fourier();
    f2.print_measure();
    printf("energy = %f\n", f2.energy());
    Fourier h = f1.AND(f2);
    h.print_all_values_fourier();
    h.print_measure();
    printf("energy = %f\n", h.energy());
    printf("meausre increase = %f\n", h.measure() / max(f1.measure(), f2.measure()));
    return 0;
}
