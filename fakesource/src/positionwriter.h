#ifndef POSITIONWRITER_H
#define POSITIONWRITER_H

#include <QDebug>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>

class PositionWriter : public QObject
{
    Q_OBJECT
private:
    QTcpServer server;
    std::vector<QTcpSocket*> clients;

public:
    PositionWriter(QObject* parent = nullptr);
    ~PositionWriter();

public slots:
    void writeCoordinates(double lat, double lon);
};

#endif // POSITIONWRITER_H
