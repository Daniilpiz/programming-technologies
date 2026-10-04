#include <iostream>
#include <vector>
#include <algorithm>

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
    setlocale(LC_ALL, "Russian");

    std::vector<int> numbers = { 15, 3, 8, 20, 8, 12, 3, 25, 10, 30, 12 };
    int minVal = 5;
    int maxVal = 20;

    std::cout << "Исходный вектор: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\nДиапазон: [" << minVal << ", " << maxVal << "]\n";

    std::vector<int> rangeUnique = getUniqueInRange(numbers, minVal, maxVal);

    std::cout << "Уникальные элементы из диапазона: ";
    for (int n : rangeUnique) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}