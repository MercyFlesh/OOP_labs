#include "server.hpp"

Server::Server(QHostAddress host, qint16 port, QObject* parent)
    :  QTcpServer(parent)
{
    if (listen(host, port))
    {
        qDebug() << "Server listening" << host << "port" << port << "";
        connect(this, SIGNAL(newConnection()), this, SLOT(conn()));
    }
    else
    {
        qDebug() << "Error start server";
        exit(EXIT_FAILURE);
    }
}


Server::~Server()
{
    for (auto& socket : clients)
    {
        socket->close();
        socket->deleteLater();
    }
}


void Server::conn()
{
    while (hasPendingConnections())
    {
        clients.append(nextPendingConnection());
        connect(qobject_cast<QAbstractSocket*>(clients[clients.size()-1]),
                SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(qobject_cast<QAbstractSocket*>(clients[clients.size()-1]),
                SIGNAL(disconnected()), this, SLOT(disc()));

        qDebug() << "client connection";
    }
}


void Server::disc()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    int index = clients.indexOf(socket);
    if (index >= 0)
    {
        clients.removeAt(index);
        qDebug() << "disconnection client";
    }
}


void Server::readyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    int index = clients.indexOf(socket);
    if (index >= 0)
    {
        QByteArray buf;
        buf = (clients.at(index))->readAll();

        emit rec(index,buf);
    }
}


void Server::send(int index, QByteArray data)
{
    if (index >= 0)
        clients.at(index)->write(data);
}
