#ifndef QGEOPOSITIONINFOSOURCEFACTORY_FAKE_H
#define QGEOPOSITIONINFOSOURCEFACTORY_FAKE_H

#include <QtCore/QObject>
#include <QtPositioning/QGeoPositionInfoSourceFactory>

class QGeoPositionInfoSourceFactoryFake : public QObject, public QGeoPositionInfoSourceFactoryV2
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "org.qt-project.qt.position.sourcefactory/5.0"
                      FILE "plugin.json")

    Q_INTERFACES(QGeoPositionInfoSourceFactoryV2)

public:
    QGeoPositionInfoSource* positionInfoSource(QObject *parent) override;
    QGeoSatelliteInfoSource* satelliteInfoSource(QObject *parent) override;
    QGeoAreaMonitorSource* areaMonitor(QObject *parent) override;
    QGeoPositionInfoSource* positionInfoSourceWithParameters(QObject *parent, const QVariantMap &parameters) override;
    QGeoSatelliteInfoSource* satelliteInfoSourceWithParameters(QObject *parent, const QVariantMap &parameters) override;
    QGeoAreaMonitorSource* areaMonitorWithParameters(QObject *parent, const QVariantMap &parameters) override;
};

#endif // QGEOPOSITIONINFOSOURCEFACTORY_FAKE_H
