#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <clocale>

std::vector<int> getUniqueInRange(const std::vector<int>& vec, int minVal, int maxVal) {
    std::vector<int> result;

    std::copy_if(vec.begin(), vec.end(), std::back_inserter(result), [minVal, maxVal](int x) {
        return x >= minVal && x <= maxVal;
        });

    std::sort(result.begin(), result.end());
    auto last = std::unique(result.begin(), result.end());
    result.erase(last, result.end());

    return result;
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

    int minVal, maxVal;
    std::cout << "\nВведите минимальное значение диапазона: ";
    std::cin >> minVal;
    std::cout << "Введите максимальное значение диапазона: ";
    std::cin >> maxVal;

    std::cout << "\nИсходный вектор: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << "\nДиапазон: [" << minVal << ", " << maxVal << "]\n";

    std::vector<int> rangeUnique = getUniqueInRange(numbers, minVal, maxVal);

    if (rangeUnique.empty()) {
        std::cout << "Нет элементов в заданном диапазоне!\n";
    } else {
        std::cout << "Уникальные элементы из диапазона: ";
        for (int num : rangeUnique) std::cout << num << " ";
        std::cout << "\n";
    }

    std::cout << "\nНажмите Enter для завершения...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
