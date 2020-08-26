#ifndef QGEOPOSITIONINFOSOURCE_FAKE_P_H
#define QGEOPOSITIONINFOSOURCE_FAKE_P_H

#include <QtPositioning/QGeoPositionInfoSource>
#include <QtCore/QPointer>
#include <QtNetwork/QTcpSocket>

class QGeoPositionInfoSourceFake : public QGeoPositionInfoSource
{
    Q_OBJECT

public:
    explicit QGeoPositionInfoSourceFake(QObject* parent = nullptr);
    ~QGeoPositionInfoSourceFake();

    // From QGeoPositionInfoSource
    void setUpdateInterval(int msec) override;
    QGeoPositionInfo lastKnownPosition(bool fromSatellitePositioningMethodsOnly = false) const override;
    PositioningMethods supportedPositioningMethods() const override;
    void setPreferredPositioningMethods(PositioningMethods methods) override;
    int minimumUpdateInterval() const override;

    Error error() const override;

    void startUpdates() override;
    void stopUpdates() override;
    void requestUpdate(int timeout = 5000) override;

    void setHost(QString const& host) { this->host = host; }
    void setPort(quint16 port) { this->port = port; }

private:
    void setError(QGeoPositionInfoSource::Error error);
    void handleNewLocation();

    QString host;
    quint16 port;
    QTcpSocket m_socket;
    QGeoPositionInfoSource::Error m_error = NoError;
    QGeoPositionInfo m_lastPosition;
};

#endif // QGEOPOSITIONINFOSOURCE_FAKE_P_H
