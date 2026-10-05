#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <windows.h>
#include <clocale>

void sortOddAscEvenDesc(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end(), [](int a, int b) {
        bool aIsOdd = (std::abs(a) % 2 == 1);
        bool bIsOdd = (std::abs(b) % 2 == 1);

        if (aIsOdd && !bIsOdd) return true;
        if (!aIsOdd && bIsOdd) return false;
        if (aIsOdd && bIsOdd) return a < b;
        return a > b;
        });
}

int main() {
    // Установить кодировку для Windows консоли
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");

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

    sortOddAscEvenDesc(numbers);

    std::cout << "Отсортированный вектор (нечётные по возр., чётные по убыв.): ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << "\n";

    std::cout << "\nНажмите Enter для завершения...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
