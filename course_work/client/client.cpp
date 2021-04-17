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
    qDebug() << "client connected";
}


void Client::disc()
{
    qDebug() << "client disconnected";
}


void Client::readyRead()
{

}
