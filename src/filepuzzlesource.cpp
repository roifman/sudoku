#include "filepuzzlesource.h"
#include <fstream>

FilePuzzleSource::FilePuzzleSource(std::string path)
    : path_(std::move(path)) {}

std::optional<Board> FilePuzzleSource::load() {
    std::ifstream in(path_);
    if (!in)
        return std::nullopt;

    Board board;
    for (int r = 0; r < Board::Size; ++r)
        for (int c = 0; c < Board::Size; ++c) {
            int v;
            if (!(in >> v))
                return std::nullopt;
            board.set(r, c, v);
            if (v != 0)
                board.setFixed(r, c, true);
        }

    return board;
}
