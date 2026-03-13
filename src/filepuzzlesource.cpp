#include "filepuzzlesource.h"
#include <fstream>

FilePuzzleSource::FilePuzzleSource(std::string path)
    : path_(std::move(path)) {}

std::optional<Board> FilePuzzleSource::load() const noexcept {
    std::ifstream in(path_);
    if (!in.is_open())
        return std::nullopt;

    Board b;

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            int v;
            if (!(in >> v))
                return std::nullopt;

            b.set(r, c, v);
        }
    }

    return b;
}
