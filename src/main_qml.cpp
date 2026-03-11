#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "sudokucontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SudokuController controller;
    engine.rootContext()->setContextProperty("sudokuController", &controller);

    engine.loadFromModule("SudokuUI", "Main");
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
