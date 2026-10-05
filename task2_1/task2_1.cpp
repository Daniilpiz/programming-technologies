#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <clocale>
#include <windows.h>

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
    // Установить кодировку для Windows консоли
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::setlocale(LC_ALL, ".UTF8");

    int n;
    std::cout << "Введите количество элементов вектора: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Количество должно быть больше нуля!\n";
        std::cout << "\nНажмите Enter для завершения...";
        std::cin.ignore();
        std::cin.get();
        return 1;
    }

    std::vector<int> numbers;
    std::cout << "Введите " << n << " чисел (разделённые пробелами или Enter):\n";
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        numbers.push_back(num);
    }

    std::cout << "\nИсходный вектор: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << "\n";

    squarePrimes(numbers);

    std::cout << "После возведения простых чисел в квадрат: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << "\n";

    std::cout << "\nНажмите Enter для завершения...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
