#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
#include <cstdio>

using namespace std;

double evaluate_fourier(const map<string, double>& coeffs, const string& point) {
    int n = point.length();
    double result = 0.0;
    
    for (const auto& [basis, coeff] : coeffs) {
        // Вычисляем скалярное произведение базисной функции и точки
        int parity = 0;
        for (int i = 0; i < n; ++i) {
            parity += (basis[i] - '0') * (point[i] - '0');
        }
        parity %= 2;
        
        // Умножаем на коэффициент и добавляем к результату
        result += coeff * pow(-1, parity);
    }
    
    return result;
} 