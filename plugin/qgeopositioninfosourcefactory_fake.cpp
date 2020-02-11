#include "qgeopositioninfosource_fake_p.h"
#include "qgeopositioninfosourcefactory_fake.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(lcPositioningFake, "qt.positioning.fake")

QGeoPositionInfoSource* QGeoPositionInfoSourceFactoryFake::positionInfoSource(QObject *parent)
{
    qCDebug(lcPositioningFake) << "positionInfoSource";
    return new QGeoPositionInfoSourceFake(parent);
}

QGeoSatelliteInfoSource* QGeoPositionInfoSourceFactoryFake::satelliteInfoSource(QObject *parent)
{
    Q_UNUSED(parent);
    return nullptr;
}

QGeoAreaMonitorSource* QGeoPositionInfoSourceFactoryFake::areaMonitor(QObject *parent)
{
    Q_UNUSED(parent);
    return nullptr;
}

QGeoPositionInfoSource* QGeoPositionInfoSourceFactoryFake::positionInfoSourceWithParameters(QObject* parent, const QVariantMap& parameters)
{
    qCDebug(lcPositioningFake) << "positionInfoSourceWithParameters";

    auto source = new QGeoPositionInfoSourceFake(parent);

    if(parameters.find("portname") == parameters.cend())
        return nullptr;

    source->setPort(parameters.find("portname").value().toString());

    return source;
}

QGeoSatelliteInfoSource* QGeoPositionInfoSourceFactoryFake::satelliteInfoSourceWithParameters(QObject* parent, const QVariantMap& parameters)
{
    Q_UNUSED(parent);
    Q_UNUSED(parameters);
    return nullptr;
}

QGeoAreaMonitorSource* QGeoPositionInfoSourceFactoryFake::areaMonitorWithParameters(QObject* parent, const QVariantMap& parameters)
{
    Q_UNUSED(parent);
    Q_UNUSED(parameters);
    return nullptr;
}
