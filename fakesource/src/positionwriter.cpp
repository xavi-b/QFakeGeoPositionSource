#include "positionwriter.h"

// https://stackoverflow.com/questions/49544318/using-linux-pseudoterminal-to-test-qserialport

PositionWriter::PositionWriter(QObject* parent)
    : QObject(parent)
{
    this->serial.setPortName("/dev/ptmx");

//    this->serial.setBaudRate(QSerialPort::Baud4800);
//    this->serial.setDataBits(QSerialPort::DataBits::Data8);

    if(!this->serial.open(QIODevice::ReadWrite))
        qDebug() << "Error opening new pseudo serial";

    int master_fd = serial.handle();

    // get device name of slave pseudoterminal
    constexpr size_t PTSNAME_BUFFER_LENGTH = 128;
    char ptsname_buffer[PTSNAME_BUFFER_LENGTH];
    if (ptsname_r(master_fd, ptsname_buffer, PTSNAME_BUFFER_LENGTH) != 0)
        return;

    // grant access to the slave
    if (grantpt(master_fd) != 0)
        return;

    // unlock the slave
    if (unlockpt(master_fd) != 0)
        return;

    this->device = ptsname_buffer;
    qDebug() << "Device" << this->device;
}

void PositionWriter::writeCoordinates(double lat, double lon)
{
    if(!this->serial.isOpen())
        if(!this->serial.open(QIODevice::ReadWrite))
            qDebug() << "Error opening new pseudo serial";

    qDebug() << "Writing" << lat << lon;
    this->serial.write((QString::number(lat, 'g', 16)+"|"+QString::number(lon, 'g', 16)).toUtf8());
}
