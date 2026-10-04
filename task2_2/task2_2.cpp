#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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
    setlocale(LC_ALL, "Russian");

    std::vector<int> numbers = { 4, 7, 2, 9, 3, 8, 1, 6, 5 };

    std::cout << "Исходный вектор: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    sortOddAscEvenDesc(numbers);

    std::cout << "Отсортированный вектор (нечётные по возр., чётные по убыв.): ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}