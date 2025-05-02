#include "fourier.hpp"
#include <iostream>

int main() {
    Fourier f({0, 1, 1, 0}, 2, "f");
    f.print_all_values_fourier();
    return 0;
}
