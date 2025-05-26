//#include "fourier.hpp"
//#include "check_xor_dnf.h"
#include "check_all_functions.h"

int main() {
    Fourier f({0, 1, 1, 0, 1, 0, 0, 1}, 3, "f");
    f.print_all_values_fourier();
    f.print_measure();
    check_all_functions(4);
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
