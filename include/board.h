#pragma once
#include <array>
#include <stdexcept>

// Board — простая модель 9×9.
class Board {
public:
    static constexpr int Size = 9;

    Board();

    int get(int row, int col) const;
    void set(int row, int col, int value);

    bool isFixed(int row, int col) const;
    void setFixed(int row, int col, bool fixed);

private:
    static constexpr bool isValidIndex(int i) noexcept {
        return i >= 0 && i < Size;
    }

    std::array<std::array<int, Size>, Size> cells_{};
    std::array<std::array<bool, Size>, Size> fixed_{};
};

