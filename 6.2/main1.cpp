#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

std::string removeWord(const std::string& sentence, const std::string& word) {
    // Split the sentence into words
    std::vector<std::string> words;
    std::string temp = "";
    for (char c : sentence) {
        if (std::isspace(c) || std::ispunct(c)) {
            if (!temp.empty()) {
                words.push_back(temp);
                temp = "";
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) {
        words.push_back(temp);
    }

    // Filter out the specified word
    words.erase(std::remove_if(words.begin(), words.end(), [&](const std::string& w) {
        return w == word;
    }), words.end());

    // Join the filtered words back into a sentence
    std::string result;
    for (const std::string& w : words) {
        result += w + " ";
    }
    result.pop_back(); // remove trailing space

    return result;
}

int main() {
    std::string sentence, word;
    std::cout << "Enter a sentence: ";
    std::getline(std::cin, sentence);
    std::cout << "Enter a word to remove: ";
    std::getline(std::cin, word);

    std::string result = removeWord(sentence, word);
    std::cout << "Result: " << result << std::endl;

    return 0;
}