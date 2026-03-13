#pragma once

#include <array>
#include <variant>
#include <string>

// CheckResult: современный способ вернуть "успех или ошибку" без bool + строка
struct CheckOk {};
struct CheckError {
    std::string message;
};

// std::variant даёт типобезопасный результат проверки
using CheckResult = std::variant<CheckOk, CheckError>;

class Board {
public:
    Board();

    // get возвращает значение клетки (0 означает пустую)
    int get(int row, int col) const;

    // set бросает исключения при нарушении инвариантов (современный, безопасный API)
    void set(int row, int col, int value);

    // clear гарантирует, что доска всегда в валидном состоянии (RAII-подход)
    void clear();

    // isValid проверяет корректность значения в позиции
    bool isValid(int row, int col, int value) const;

    // solve использует backtracking для поиска решения
    bool solve();

    // isSolved проверяет, что доска полностью и корректно заполнена
    bool isSolved() const;

    // check возвращает variant вместо bool + сообщение
    CheckResult check() const;

    // оператор копирования — безопасный и простой
    Board& operator=(const Board& other);

private:
    // cells_ хранит текущее состояние доски
    std::array<std::array<int, 9>, 9> cells_;

    // рекурсивный backtracking-алгоритм
    bool solveRecursive(int row, int col);
};
