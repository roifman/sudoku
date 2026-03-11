#pragma once
#include <optional>
#include "board.h"

// Интерфейс источника головоломки.
// Используем std::optional для безопасной загрузки.
class IPuzzleSource {
public:
    virtual ~IPuzzleSource() = default;
    virtual std::optional<Board> load() = 0;
};
