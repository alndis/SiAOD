#include <iostream>
#include <string>
#include <vector>

std::string longestPalindromicSubstring(const std::string& str) {
    int n = str.length();
    std::string longest = "";

    for (int i = 0; i < n; i++) {
        // ищем палиндромы с нечетной длиной
        int l = i, r = i;
        while (l >= 0 && r < n && str[l] == str[r]) {
            l--;
            r++;
        }
        std::string palindrome = str.substr(l + 1, r - l - 1);
        if (palindrome.length() > longest.length()) {
            longest = palindrome;
        }

        // ищем палиндромы с четной длиной
        l = i;
        r = i + 1;
        while (l >= 0 && r < n && str[l] == str[r]) {
            l--;
            r++;
        }
        palindrome = str.substr(l + 1, r - l - 1);
        if (palindrome.length() > longest.length()) {
            longest = palindrome;
        }
    }

    return longest;
}
int main() {
    std::string str;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);

    std::string result = longestPalindromicSubstring(str);
    std::cout << "Longest palindromic substring: " << result << std::endl;

    return 0;
}