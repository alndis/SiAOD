#include <iostream>
#include <vector>

using namespace std;

int countWays(int n, int m) {
    // Создаем двумерный вектор для хранения количества способов
    vector<vector<int>> dp(n, vector<int>(m, 0));
    // Инициализация начальной позиции
    dp[0][0] = 1;
    // Заполнение массива dp
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Если мы не на первой строке, добавляем способы из верхней клетки
            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            // Если мы не в первом столбце, добавляем способы из левой клетки
            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
    // Возвращаем количество способов добраться до нижнего правого угла
    return dp[n - 1][m - 1];
}

int main() {
    int n, m;
    cout << "Введите размеры поля (n m): ";
    cin >> n >> m;

    int ways = countWays(n, m);
    cout << "Количество способов добраться до правого нижнего угла: " << ways << endl;

    return 0;
}
