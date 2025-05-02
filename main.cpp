#include "fourier.hpp"
#include <iostream>

int main() {
    Fourier f = fourier_decomposition({0, 0, 0, 1}, 2);
    print_all_values_fourier(f, "f");
    return 0;
}
