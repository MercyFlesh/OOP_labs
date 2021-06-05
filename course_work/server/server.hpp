#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

#include <memory>


class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QHostAddress host, qint16 port, QObject* parent = nullptr);
    ~Server();

public slots:
    void conn();
    void disc();
    void readyRead();
    void send(int index, QByteArray message);

signals:
    void rec(int,QByteArray);

private:
    QVector<QTcpSocket*> clients;
};
