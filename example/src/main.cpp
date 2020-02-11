#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>
#include <QDebug>
#include <QGeoPositionInfoSource>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QLoggingCategory::setFilterRules("default.debug=true\n"
                                     "qt.positioning.fake.debug=true");

    qDebug() << "Sources" << QGeoPositionInfoSource::availableSources();

//    QVariantMap params;
//    params.insert("portname", "/dev/pts/2");
//    QGeoPositionInfoSource* source = QGeoPositionInfoSource::createSource("fake", params, nullptr);
//    QObject::connect(source, &QGeoPositionInfoSource::positionUpdated, [=](QGeoPositionInfo const& pos)
//    {
//        qDebug() << "pos" << pos;
//    });
//    source->setUpdateInterval(1000);
//    source->startUpdates();

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:///qml/Main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
