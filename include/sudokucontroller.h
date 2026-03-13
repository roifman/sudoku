#pragma once

#include <QObject>
#include <memory>
#include "board.h"
#include "filepuzzlesource.h"
#include "solver.h"

// SudokuController: мост между QML и C++ (современный MVC-подход)
class SudokuController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int revision READ revision NOTIFY boardChanged)

public:
    explicit SudokuController(QObject* parent = nullptr);

    // Q_INVOKABLE — современный способ вызывать C++ из QML
    Q_INVOKABLE int getCell(int row, int col) const;
    Q_INVOKABLE void setCell(int row, int col, int value);
    Q_INVOKABLE void solve();
    Q_INVOKABLE void generatePuzzle();
    Q_INVOKABLE void loadPuzzle();
    Q_INVOKABLE void checkSolved();
    Q_INVOKABLE void hint();

    int revision() const { return revision_; }

signals:
    void boardChanged();
    void invalidInput(QString message);

private:
    // unique_ptr подчёркивает владение ресурсами (RAII)
    std::unique_ptr<Board> board_;

    // optional-ориентированная загрузка пазлов
    std::unique_ptr<FilePuzzleSource> testSource_;

    // shared_ptr — пример совместного владения solver'ом
    std::shared_ptr<Solver> solver_;

    bool hasInvalidInput_ = false;
    int revision_ = 0;

    // touchBoard обновляет UI через Q_PROPERTY
    void touchBoard();
};
