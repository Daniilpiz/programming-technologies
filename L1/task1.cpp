#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

std::string cleanWord(std::string word) {
    while (!word.empty() && ispunct(static_cast<unsigned char>(word.back()))) {
        word.pop_back();
    }
    while (!word.empty() && ispunct(static_cast<unsigned char>(word.front()))) {
        word.erase(0, 1);
    }
    std::transform(word.begin(), word.end(), word.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return word;
}

void processFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    std::map<std::string, int> wordCount;
    std::map<std::string, std::vector<int>> wordPositions;

    std::string rawWord;
    int pos = 0;

    while (file >> rawWord) {
        if (rawWord == "—" || rawWord == "-") continue;
        std::string word = cleanWord(rawWord);
        if (word.empty()) continue;

        wordCount[word]++;
        wordPositions[word].push_back(pos);
        pos++;
    }

    std::cout << "--- Подсчет уникальных слов ---\n";
    for (const auto& pair : wordCount) {
        std::cout << pair.first << " - " << pair.second << "\n";
    }

    std::cout << "\n--- Индексация позиций ---\n";
    for (const auto& pair : wordPositions) {
        std::cout << pair.first << " – ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            std::cout << pair.second[i] << (i + 1 == pair.second.size() ? "" : ", ");
        }
        std::cout << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаем тестовый файл согласно примеру из задания
    std::ofstream testFile("test.txt");
    testFile << "Свобода творчества — свобода делать ошибки";
    testFile.close();

    processFile("test.txt");

    return 0;
}