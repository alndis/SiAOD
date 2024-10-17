#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

// Структура для хранения символов и их вероятностей
struct Symbol {
    char character;
    double probability;
    std::string code;
};

// Функция для сравнения по вероятности
bool compareByProbability(const Symbol &a, const Symbol &b) {
    return a.probability > b.probability;
}

// Рекурсивная функция для генерации кодов Шеннона-Фано
void shannonFanoCode(std::vector<Symbol> &symbols, int start, int end) {
    if (start >= end) return;

    // Находим середину по вероятностям
    int splitIndex = start;
    double totalProbLeft = 0, totalProbRight = 0;

    for (int i = start; i <= end; ++i) {
        totalProbRight += symbols[i].probability;
    }

    double diff = totalProbRight;
    for (int i = start; i <= end; ++i) {
        totalProbLeft += symbols[i].probability;
        totalProbRight -= symbols[i].probability;

        if (std::abs(totalProbLeft - totalProbRight) < diff) {
            diff = std::abs(totalProbLeft - totalProbRight);
            splitIndex = i;
        }
    }

    // Присваиваем 0 для одной половины, 1 для другой
    for (int i = start; i <= splitIndex; ++i) {
        symbols[i].code += "0";
    }
    for (int i = splitIndex + 1; i <= end; ++i) {
        symbols[i].code += "1";
    }

    // Рекурсивно обрабатываем обе половины
    shannonFanoCode(symbols, start, splitIndex);
    shannonFanoCode(symbols, splitIndex + 1, end);
}

// Основная функция кодирования текста
std::string encodeText(const std::string &text, std::map<char, std::string> &encodingMap) {
    std::string encodedText;
    for (char ch : text) {
        encodedText += encodingMap[ch];
    }
    return encodedText;
}

// Функция декодирования текста
std::string decodeText(const std::string &encodedText, const std::map<std::string, char> &decodingMap) {
    std::string decodedText;
    std::string temp;
    for (char bit : encodedText) {
        temp += bit;
        if (decodingMap.find(temp) != decodingMap.end()) {
            decodedText += decodingMap.at(temp);
            temp.clear();
        }
    }
    return decodedText;
}

// Функция для вычисления процента сжатия
double calculateCompressionRatio(const std::string &originalText, const std::string &encodedText) {
    return 100.0 * (1.0 - (static_cast<double>(encodedText.size()) / (originalText.size() * 8)));
}

int main() {
    std::string inputText;
    std::ifstream inputFile("input.txt");
    
    // Чтение текста из файла
    if (inputFile.is_open()) {
        std::getline(inputFile, inputText, '\0'); // Считываем весь текст
        inputFile.close();
    } else {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    // Подсчет частоты символов
    std::map<char, int> frequencyMap;
    for (char ch : inputText) {
        frequencyMap[ch]++;
    }

    // Создание списка символов с вероятностями
    std::vector<Symbol> symbols;
    for (const auto &pair : frequencyMap) {
        symbols.push_back({pair.first, static_cast<double>(pair.second) / inputText.size(), ""});
    }

    // Сортируем символы по вероятности
    std::sort(symbols.begin(), symbols.end(), compareByProbability);

    // Генерируем коды
    shannonFanoCode(symbols, 0, symbols.size() - 1);

    // Создаем карты для кодирования и декодирования
    std::map<char, std::string> encodingMap;
    std::map<std::string, char> decodingMap;
    for (const auto &symbol : symbols) {
        encodingMap[symbol.character] = symbol.code;
        decodingMap[symbol.code] = symbol.character;
    }

    // Кодируем текст
    std::string encodedText = encodeText(inputText, encodingMap);

    // Декодируем текст
    std::string decodedText = decodeText(encodedText, decodingMap);

    // Вывод результатов
    std::ofstream encodedFile("encoded.txt");
    encodedFile << encodedText;
    encodedFile.close();

    std::ofstream decodedFile("decoded.txt");
    decodedFile << decodedText;
    decodedFile.close();

    // Вывод процента сжатия
    double compressionRatio = calculateCompressionRatio(inputText, encodedText);
    std::cout << "Процент сжатия: " << compressionRatio << "%" << std::endl;

    return 0;
}
