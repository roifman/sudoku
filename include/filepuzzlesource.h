#pragma once

#include <string>
#include <optional>
#include "board.h"

// FilePuzzleSource: современный способ загрузки данных с использованием std::optional
class FilePuzzleSource {
public:
    explicit FilePuzzleSource(std::string path);

    // load возвращает optional — явный способ выразить "может не загрузиться"
    std::optional<Board> load() const noexcept;

private:
    std::string path_;
};
