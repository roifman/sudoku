#pragma once
#include <optional>
#include "board.h"

class IPuzzleSource {
public:
    virtual ~IPuzzleSource() = default;
    virtual std::optional<Board> load() = 0;
};
