#include "qgeopositioninfosource_fake_p.h"

#include <QtCore/QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(lcPositioningFake)

QGeoPositionInfoSourceFake::QGeoPositionInfoSourceFake(QObject *parent)
    : QGeoPositionInfoSource(parent)
{
    qCDebug(lcPositioningFake) << "Fake ready";
}

QGeoPositionInfoSourceFake::~QGeoPositionInfoSourceFake()
{

}

void QGeoPositionInfoSourceFake::setUpdateInterval(int msec)
{
    QGeoPositionInfoSource::setUpdateInterval(msec);
}

QGeoPositionInfo QGeoPositionInfoSourceFake::lastKnownPosition(bool fromSatellitePositioningMethodsOnly) const
{
    if (fromSatellitePositioningMethodsOnly)
        return QGeoPositionInfo();
    return this->m_lastPosition;
}

QGeoPositionInfoSourceFake::PositioningMethods QGeoPositionInfoSourceFake::supportedPositioningMethods() const
{
    return AllPositioningMethods;
}

void QGeoPositionInfoSourceFake::setPreferredPositioningMethods(PositioningMethods methods)
{
    QGeoPositionInfoSource::setPreferredPositioningMethods(methods);
}

int QGeoPositionInfoSourceFake::minimumUpdateInterval() const
{
    return QGeoPositionInfoSource::minimumUpdateInterval();
}

QGeoPositionInfoSource::Error QGeoPositionInfoSourceFake::error() const
{
    return this->m_error;
}

void QGeoPositionInfoSourceFake::startUpdates()
{
    if(this->m_socket.isOpen())
    {
        qCDebug(lcPositioningFake) << "The slave port is already opened";
        return;
    }

    this->m_socket.connectToHost(host, port, QIODevice::ReadOnly);

    if(!this->m_socket.waitForConnected())
    {
        qCDebug(lcPositioningFake) << "The slave port has not connected" << this->m_socket.errorString();
        this->setError(QGeoPositionInfoSource::AccessError);
        return;
    }

    qCDebug(lcPositioningFake) << "Starting updates";

    connect(&this->m_socket, &QTcpSocket::readyRead, this, &QGeoPositionInfoSourceFake::handleNewLocation);
}

void QGeoPositionInfoSourceFake::stopUpdates()
{
    this->m_socket.disconnectFromHost();

    qCDebug(lcPositioningFake) << "Stopping updates";

    disconnect(&this->m_socket, &QTcpSocket::readyRead, this, &QGeoPositionInfoSourceFake::handleNewLocation);
}

void QGeoPositionInfoSourceFake::requestUpdate(int timeout)
{
    emit positionUpdated(this->m_lastPosition);
}

void QGeoPositionInfoSourceFake::setError(QGeoPositionInfoSource::Error error)
{
    this->m_error = error;
    emit QGeoPositionInfoSource::error(this->m_error);
}

void QGeoPositionInfoSourceFake::handleNewLocation()
{
    QString data = this->m_socket.readAll();
    qCDebug(lcPositioningFake) << "Received: " << data;
    QStringList c = data.split('|');

    if(c.size() < 2)
        return;

    double lat = c[0].toDouble();
    double lon = c[1].toDouble();
    this->m_lastPosition.setCoordinate(QGeoCoordinate(lat, lon));
    emit positionUpdated(this->m_lastPosition);
}
