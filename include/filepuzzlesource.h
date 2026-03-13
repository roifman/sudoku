#pragma once

#include <string>
#include <optional>
#include "board.h"

class FilePuzzleSource {
public:
    explicit FilePuzzleSource(std::string path);
    std::optional<Board> load() const noexcept;

private:
    std::string path_;
};
