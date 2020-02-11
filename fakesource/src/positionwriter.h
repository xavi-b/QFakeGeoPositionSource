#ifndef POSITIONWRITER_H
#define POSITIONWRITER_H

#include <QSerialPort>
#include <QDebug>
#include <QThread>

class PositionWriter : public QObject
{
    Q_OBJECT
private:
    QSerialPort serial;
    QString device;

public:
    PositionWriter(QObject* parent = nullptr);

    QString getDevice() const { return this->device; }

public slots:
    void writeCoordinates(double lat, double lon);
};

#endif // POSITIONWRITER_H
