#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include "positionwriter.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    PositionWriter instance;

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:///qml/Main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject::connect(engine.rootObjects().first(), SIGNAL(coordinatesChanged(double, double)),
                     &instance, SLOT(writeCoordinates(double, double)));

    if(a.arguments().count("--hide"))
    {
        engine.rootObjects().first()->setProperty("visible", false);
        qDebug() << "invokeMethod:" << QMetaObject::invokeMethod(engine.rootObjects().first(), "toggle");
    }

    return a.exec();
}
