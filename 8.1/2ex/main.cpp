#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <fstream>
#include <locale>

using namespace std;

// Узел дерева Хаффмана
struct Node {
    wchar_t character;  // Используем wchar_t для поддержки символов Unicode
    int frequency;
    Node *left, *right;

    Node(wchar_t character, int frequency) {
        left = right = nullptr;
        this->character = character;
        this->frequency = frequency;
    }
};

// Сравнение для очереди с приоритетами
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

// Рекурсивная функция для генерации кодов
void generateHuffmanCodes(Node* root, wstring code, map<wchar_t, wstring>& huffmanCodes) {
    if (!root)
        return;

    // Если это лист, сохраняем код
    if (!root->left && !root->right) {
        huffmanCodes[root->character] = code;
    }

    generateHuffmanCodes(root->left, code + L"0", huffmanCodes);
    generateHuffmanCodes(root->right, code + L"1", huffmanCodes);
}

// Функция для построения дерева Хаффмана и получения кодов
map<wchar_t, wstring> buildHuffmanTree(const wstring& text) {
    // Подсчет частоты символов
    map<wchar_t, int> frequencyMap;
    for (wchar_t ch : text) {
        frequencyMap[ch]++;
    }

    // Очередь с приоритетами для построения дерева Хаффмана
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Создание узлов для каждого символа
    for (auto pair : frequencyMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Построение дерева Хаффмана
    while (minHeap.size() != 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        int sum = left->frequency + right->frequency;
        Node* newNode = new Node(L'\0', sum);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    // Генерация кодов Хаффмана
    map<wchar_t, wstring> huffmanCodes;
    generateHuffmanCodes(minHeap.top(), L"", huffmanCodes);

    return huffmanCodes;
}

// Кодирование текста
wstring encodeText(const wstring& text, map<wchar_t, wstring>& huffmanCodes) {
    wstring encodedText = L"";
    for (wchar_t ch : text) {
        encodedText += huffmanCodes[ch];
    }
    return encodedText;
}

// Декодирование текста
wstring decodeText(Node* root, const wstring& encodedText) {
    wstring decodedText = L"";
    Node* currentNode = root;
    for (wchar_t bit : encodedText) {
        if (bit == L'0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        // Если мы достигли листа, добавляем символ к результату
        if (!currentNode->left && !currentNode->right) {
            decodedText += currentNode->character;
            currentNode = root;
        }
    }
    return decodedText;
}

// Основная функция
int main() {
    // Устанавливаем локаль для поддержки UTF-8 и кириллицы
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wstring text = L"Сидиков Никита Александрович";

    // Построение дерева Хаффмана и получение кодов
    map<wchar_t, wstring> huffmanCodes = buildHuffmanTree(text);

    // Вывод кодов для каждого символа
    wcout << L"Коды Хаффмана для каждого символа:\n";
    for (auto pair : huffmanCodes) {
        wcout << pair.first << L": " << pair.second << endl;
    }

    // Кодирование текста
    wstring encodedText = encodeText(text, huffmanCodes);

    wcout << L"\nЗакодированный текст:\n" << encodedText << endl;

    // Восстановление текста из кода
    // Для декодирования нужно повторно построить дерево Хаффмана
    Node* root = nullptr;
    map<wchar_t, int> frequencyMap;
    for (wchar_t ch : text) {
        frequencyMap[ch]++;
    }
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (auto pair : frequencyMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }
    while (minHeap.size() != 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();
        int sum = left->frequency + right->frequency;
        Node* newNode = new Node(L'\0', sum);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }
    root = minHeap.top();

    wstring decodedText = decodeText(root, encodedText);

    wcout << L"\nДекодированный текст:\n" << decodedText << endl;

    return 0;
}
