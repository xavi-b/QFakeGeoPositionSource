#include "positionwriter.h"

PositionWriter::PositionWriter(QObject* parent)
    : QObject(parent)
{
    this->server.listen(QHostAddress::Any, 50000);

    connect(&this->server, &QTcpServer::newConnection, this, [=](){
        QTcpSocket* clientConnection = this->server.nextPendingConnection();
        this->clients.push_back(clientConnection);
        connect(clientConnection, &QAbstractSocket::disconnected, this, [=](){
            auto it = std::find(this->clients.begin(), this->clients.end(), clientConnection);
            if(it != this->clients.end())
                this->clients.erase(it);

            clientConnection->deleteLater();
        });
    });
}

PositionWriter::~PositionWriter()
{
    for(auto c : this->clients)
        c->deleteLater();
}

void PositionWriter::writeCoordinates(double lat, double lon)
{
    for(auto c : this->clients)
        c->write((QString::number(lat, 'g', 16)+"|"+QString::number(lon, 'g', 16)).toUtf8()+"|");
}
