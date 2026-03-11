#pragma once
#include "ipuzzlesource.h"
#include <string>

// FilePuzzleSource — загрузка судоку из текстового файла.
class FilePuzzleSource : public IPuzzleSource {
public:
    explicit FilePuzzleSource(std::string path);
    std::optional<Board> load() override;

private:
    std::string path_;
};
