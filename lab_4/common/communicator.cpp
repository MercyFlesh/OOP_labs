#include "communicator.hpp"

Communicator::Communicator(QHostAddress host,
                           quint16 port,
                           QObject* parent)
    : QUdpSocket(parent), host_(host), port_(port)
{
      if(bind(host, port))
          connect(this, SIGNAL(readyRead()), this, SLOT(readyRead()));
}


void Communicator::readyRead()
{
    if (hasPendingDatagrams())
    {
        QByteArray buf;
        buf.resize(pendingDatagramSize());
        readDatagram(buf.data(), buf.size());

        rec(buf);
    }
}


void Communicator::send_msg(QByteArray msg)
{
    writeDatagram(msg, host_, port_);
}
