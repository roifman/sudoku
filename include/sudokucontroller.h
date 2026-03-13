#pragma once

#include <QObject>
#include <memory>
#include "board.h"
#include "filepuzzlesource.h"
#include "solver.h"

//QML -> C++
class SudokuController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int revision READ revision NOTIFY boardChanged)

public:
    explicit SudokuController(QObject* parent = nullptr);

    //способ вызывать C++ из QML
    Q_INVOKABLE int getCell(int row, int col) const;
    Q_INVOKABLE void setCell(int row, int col, int value);
    Q_INVOKABLE void solve();
    Q_INVOKABLE void generatePuzzle();
    Q_INVOKABLE void loadPuzzle();
    Q_INVOKABLE void checkSolved();
    Q_INVOKABLE void hint();
    Q_INVOKABLE void generateEasy();
    Q_INVOKABLE void generateMedium();
    Q_INVOKABLE void generateHard();

    int revision() const { return revision_; }

signals:
    void boardChanged();
    void invalidInput(QString message);

private:
    // unique_ptr
    std::unique_ptr<Board> board_;

    // optional
    std::unique_ptr<FilePuzzleSource> testSource_;

    // shared_ptr
    std::shared_ptr<Solver> solver_;

    bool hasInvalidInput_ = false;
    int revision_ = 0;

    //обновляет UI через Q_PROPERTY
    void touchBoard();
    void generatePuzzleWithDifficulty(int level);
};
