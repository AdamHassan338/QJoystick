#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QQmlContext>
#include "serialreader.h"
#include <QThread>
int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SerialReader* serialReader = new SerialReader();
    engine.rootContext()->setContextProperty("serialReader", serialReader);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qjoystick", "Main");

    return app.exec();
}
