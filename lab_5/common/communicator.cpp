#include "communicator.hpp"


Communicator::Communicator(QHostAddress rec_host, quint16 rec_port,
                           QHostAddress send_host, quint16 send_port,
                           QObject* parent)
    : QUdpSocket(parent), senderHost(send_host), senderPort(send_port)
{
      if(bind(rec_host, rec_port))
          connect(this, SIGNAL(readyRead()), this, SLOT(readyRead()));
}


void Communicator::readyRead()
{
    if (hasPendingDatagrams())
    {
        QByteArray buf;
        buf.resize(pendingDatagramSize());
        readDatagram(buf.data(), buf.size(), &senderHost, &senderPort);

        emit rec(buf);
    }
}


void Communicator::send_msg(QByteArray msg)
{
    writeDatagram(msg, senderHost, senderPort);
}
