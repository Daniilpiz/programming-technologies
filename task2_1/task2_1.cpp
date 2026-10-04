#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <clocale>

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void squarePrimes(std::vector<int>& vec) {
    std::transform(vec.begin(), vec.end(), vec.begin(), [](int x) {
        return isPrime(x) ? (x * x) : x;
        });
}

int main() {
    // Установить локаль по умолчанию окружения — это корректно работает в разных системах
    std::setlocale(LC_ALL, "");

    std::vector<int> numbers = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    std::cout << "Исходный вектор: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    squarePrimes(numbers);

    std::cout << "После возведения простых чисел в квадрат: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}