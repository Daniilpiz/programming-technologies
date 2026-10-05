#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <clocale>
#include <algorithm>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

// Кроссплатформная очистка слова от пунктуации
std::string cleanWord(std::string word) {
	// Удалить пунктуацию с конца
	while (!word.empty() && std::ispunct(static_cast<unsigned char>(word.back()))) {
		word.pop_back();
	}
	// Удалить пунктуацию с начала
	while (!word.empty() && std::ispunct(static_cast<unsigned char>(word.front()))) {
		word.erase(0, 1);
	}
	// Преобразовать в нижний регистр
	std::transform(word.begin(), word.end(), word.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return word;
}

void processFile(const std::string& filename, const std::string& outputFilenameFirst,
	const std::string& outputFilenameSecond) {

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Не удалось открыть файл. Проверьте путь!\n";
		return;
	}

	std::map<std::string, int> wordCount;
	std::map<std::string, std::vector<int>> wordPositions;

	std::string rawWord;
	int pos = 0;

	// Читаем слова
	while (file >> rawWord) {
		// Пропустить служебные символы
		if (rawWord == "—" || rawWord == "-" || rawWord == "–") continue;

		std::string word = cleanWord(rawWord);
		if (word.empty()) continue;

		wordCount[word]++;
		wordPositions[word].push_back(pos);
		pos++;
	}

	// === Вывод в КОНСОЛЬ (с ограничением 30 строк) ===
	std::cout << "=== Подсчет уникальных слов (всего: " << wordCount.size() << ") ===\n";
	int printLimit = 0;
	for (const auto& pair : wordCount) {
		std::cout << pair.first << " - " << pair.second << "\n";
		if (++printLimit >= 30) {
			std::cout << "... [в консоли показаны только первые 30. Полные списки сохранены в файлах]\n";
			break;
		}
	}

	std::cout << "\n=== Индексация позиций ===\n";
	printLimit = 0;
	for (const auto& pair : wordPositions) {
		std::cout << pair.first << " – ";
		for (size_t i = 0; i < pair.second.size(); ++i) {
			std::cout << pair.second[i] << (i + 1 == pair.second.size() ? "" : ", ");
		}
		std::cout << "\n";
		if (++printLimit >= 30) {
			std::cout << "... [в консоли показаны только первые 30. Полные списки сохранены в файлах]\n";
			break;
		}
	}

	// === Запись ФАЙЛА 1: Подсчет уникальных слов ===
	std::ofstream outFile1(outputFilenameFirst);
	if (outFile1.is_open()) {
		outFile1 << "=== Подсчет уникальных слов (всего: " << wordCount.size() << ") ===\n";
		for (const auto& pair : wordCount) {
			outFile1 << pair.first << " - " << pair.second << "\n";
		}
		outFile1.close();
	}

	// === Запись ФАЙЛА 2: Индексация позиций слов ===
	std::ofstream outFile2(outputFilenameSecond);
	if (outFile2.is_open()) {
		outFile2 << "=== Индексация позиций слов ===\n";
		for (const auto& pair : wordPositions) {
			outFile2 << pair.first << " – ";
			for (size_t i = 0; i < pair.second.size(); ++i) {
				outFile2 << pair.second[i];
				if (i + 1 != pair.second.size()) {
					outFile2 << ", ";
				}
			}
			outFile2 << "\n";
		}
		outFile2.close();
	}

	std::cout << "\nУспешно! Результаты сохранены в файлы:\n";
	std::cout << " 1. " << outputFilenameFirst << "\n";
	std::cout << " 2. " << outputFilenameSecond << "\n";
}

int main() {
	// Установить кодировку для Windows консоли
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	std::setlocale(LC_ALL, ".UTF8");

	std::string filename = "war_and_peace.txt";
	std::string outputFilenameFirst = "output_1.txt";
	std::string outputFilenameSecond = "output_2.txt";

	std::cout << "Обработка файла: " << filename << "\n\n";

	processFile(filename, outputFilenameFirst, outputFilenameSecond);

	std::cout << "\nНажмите Enter для завершения...";
	std::cin.get();

	return 0;
}
