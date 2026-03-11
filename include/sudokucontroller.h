#pragma once
#include <QObject>
#include <QVariantList>
#include <memory>

#include "board.h"
#include "ipuzzlesource.h"

// SudokuController — мост между QML и C++.
class SudokuController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList board READ board NOTIFY boardChanged)

public:
    explicit SudokuController(QObject* parent = nullptr);

    Q_INVOKABLE void setCell(int row, int col, int value);
    Q_INVOKABLE void reset();

    QVariantList board() const;

signals:
    void boardChanged();

private:
    std::shared_ptr<Board> board_;
    std::unique_ptr<IPuzzleSource> source_;

    void loadInitial();
};

