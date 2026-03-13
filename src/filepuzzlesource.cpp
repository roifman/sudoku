#include "filepuzzlesource.h"
#include <fstream>
#include <QCoreApplication>
#include <QDir>
#include <QFile>

FilePuzzleSource::FilePuzzleSource(std::string path)
    : path_(std::move(path)) {}

std::optional<Board> FilePuzzleSource::load() const noexcept {
    QString exeDir = QCoreApplication::applicationDirPath();

    // Try to load puzzle.txt from the same directory as the executable
    QString absolutePath = QDir(exeDir).filePath(QString::fromStdString(path_));

    // If not found, try project root (one level above build/)
    if (!QFile::exists(absolutePath)) {
        absolutePath = QDir(exeDir + "/..").filePath(QString::fromStdString(path_));
    }

    std::ifstream in(absolutePath.toStdString());
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
