#include "fourier.hpp"
#include <iostream>

int main() {
    vector<bool> truth_table_f = {0, 1, 1, 1, 1, 0, 1, 1};
    Fourier f(truth_table_f, 3, "f");

    vector<bool> truth_table_g = {0, 1, 1, 1, 1, 1, 1, 1};
    Fourier g(truth_table_g, 3, "g");

    Fourier h = f.convolution(g);
    h.print_all_values_fourier();
    f.print_all_values_fourier();
    return 0;
}
