#include "client.hpp"

Client::Client(QHostAddress host, qint16 port,
               QObject* parent)
    : QObject(parent),
      socket_ptr(new QTcpSocket(this))
{
    socket_ptr->connectToHost(host, port);

    connect(socket_ptr.get(), SIGNAL(connected()), this, SLOT(conn()));
    connect(socket_ptr.get(), SIGNAL(disconnected()), this, SLOT(disc()));
    connect(socket_ptr.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));
}


void Client::conn()
{
    qDebug() << "connected to server";
}


void Client::disc()
{
    qDebug() << "disconnected from server";
}


void Client::readyRead()
{
    if(socket_ptr->waitForConnected(500))
    {
        QByteArray data = socket_ptr->readAll();
        emit accept_response(data);
    }
}


void Client::send_data(QByteArray data)
{
    if(socket_ptr->state() == QAbstractSocket::ConnectedState)
    {
            socket_ptr->write(data);
            socket_ptr->waitForBytesWritten(500);
    }
}
