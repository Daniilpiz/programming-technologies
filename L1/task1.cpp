#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cwctype>
#include <windows.h> // Использование Win32 API
#include <fcntl.h>
#include <io.h>

// Надежная конвертация UTF-8 в широкие символы (Юникод) через Win32 API
std::wstring utf8_to_wstring(const std::string& str) {
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// Конвертация Юникода обратно в UTF-8 для записи в файл
std::string wstring_to_utf8(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

std::wstring cleanWord(std::wstring word) {
    std::wstring puncts = L".,!?;:-—–«»\"'()[]…“”";

    while (!word.empty() && (std::iswpunct(word.back()) || puncts.find(word.back()) != std::wstring::npos)) {
        word.pop_back();
    }
    while (!word.empty() && (std::iswpunct(word.front()) || puncts.find(word.front()) != std::wstring::npos)) {
        word.erase(0, 1);
    }
    for (auto& ch : word) {
        ch = std::towlower(ch);
    }
    return word;
}

void processFile(const std::string& filename, const std::string& outputFilenameFirst,
    const std::string& outputFilenameSecond) {
    // Читаем входной файл как обычные байты (UTF-8)
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::wcerr << L"Не удалось открыть файл. Проверьте путь!\n";
        return;
    }

    std::map<std::wstring, int> wordCount;
    std::map<std::wstring, std::vector<int>> wordPositions;

    std::string rawWordUtf8;
    int pos = 0;

    // Считываем слова
    while (file >> rawWordUtf8) {
        std::wstring rawWord = utf8_to_wstring(rawWordUtf8);

        if (rawWord == L"—" || rawWord == L"-" || rawWord == L"–") continue;

        std::wstring word = cleanWord(rawWord);
        if (word.empty()) continue;

        wordCount[word]++;
        wordPositions[word].push_back(pos);
        pos++;
    }

    // === Вывод в КОНСОЛЬ (с ограничением 30 строк) ===
    std::wcout << L"=== Подсчет уникальных слов (всего: " << wordCount.size() << L") ===\n";
    int printLimit = 0;
    for (const auto& pair : wordCount) {
        std::wcout << pair.first << L" - " << pair.second << L"\n";
        if (++printLimit >= 30) {
            std::wcout << L"... [в консоли показаны только первые 30. Полные списки сохранены в файлах]\n";
            break;
        }
    }

    std::wcout << L"\n=== Индексация позиций ===\n";
    printLimit = 0;
    for (const auto& pair : wordPositions) {
        std::wcout << pair.first << L" – ";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            std::wcout << pair.second[i] << (i + 1 == pair.second.size() ? L"" : L", ");
        }
        std::wcout << L"\n";
        if (++printLimit >= 30) {
            std::wcout << L"... [в консоли показаны только первые 30. Полные списки сохранены в файлах]\n";
            break;
        }
    }

    // === Запись ФАЙЛА №1: Подсчет уникальных слов ===
    std::ofstream outFile1(outputFilenameFirst, std::ios::binary);
    if (outFile1.is_open()) {
        outFile1 << "\xEF\xBB\xBF"; // BOM для UTF-8
        std::wstring buffer1 = L"=== Подсчет уникальных слов (всего: " + std::to_wstring(wordCount.size()) + L") ===\r\n";
        for (const auto& pair : wordCount) {
            buffer1 += pair.first + L" - " + std::to_wstring(pair.second) + L"\r\n";
        }
        outFile1 << wstring_to_utf8(buffer1);
        outFile1.close();
    }

    // === Запись ФАЙЛА №2: Индексация позиций слов ===
    std::ofstream outFile2(outputFilenameSecond, std::ios::binary);
    if (outFile2.is_open()) {
        outFile2 << "\xEF\xBB\xBF"; // BOM для UTF-8
        std::wstring buffer2 = L"=== Индексация позиций слов ===\r\n";
        for (const auto& pair : wordPositions) {
            buffer2 += pair.first + L" – ";
            for (size_t i = 0; i < pair.second.size(); ++i) {
                buffer2 += std::to_wstring(pair.second[i]);
                if (i + 1 != pair.second.size()) {
                    buffer2 += L", ";
                }
            }
            buffer2 += L"\r\n";
        }
        outFile2 << wstring_to_utf8(buffer2);
        outFile2.close();
    }

    std::wcout << L"\nУспешно! Результаты сохранены в файлы:\n";
    std::wcout << L" 1. " << utf8_to_wstring(outputFilenameFirst) << L"\n";
    std::wcout << L" 2. " << utf8_to_wstring(outputFilenameSecond) << L"\n";
}

int main() {
    // Перевод консоли в режим отображения Юникода (UTF-16)
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);

    std::string filename = "war_and_peace.txt";
    std::string outputFilenameFirst = "output_1.txt";
    std::string outputFilenameSecond = "output_2.txt";

    std::wcout << L"Обработка файла: " << utf8_to_wstring(filename) << L"\n\n";

    processFile(filename, outputFilenameFirst, outputFilenameSecond);

    return 0;
}