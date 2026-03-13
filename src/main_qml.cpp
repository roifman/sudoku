#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "sudokucontroller.h"
using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<SudokuController>("Sudoku", 1, 0, "SudokuController");

    const QUrl url(u"qrc:/qml/main.qml"_s);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );

    engine.load(url);

    return app.exec();
}
