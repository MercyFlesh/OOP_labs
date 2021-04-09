#pragma once

#include <QObject>
#include <QUdpSocket>

class Communicator : public QUdpSocket
{
    Q_OBJECT

    QHostAddress senderHost;
    quint16 senderPort;
    QHostAddress receiverHost;
    quint16 receiverPort;

public:
    explicit Communicator(QHostAddress rec_host, quint16 rec_port,
                          QHostAddress send_host, quint16 send_port,
                          QObject* parent = nullptr);

signals:
    void rec(QByteArray msg);

public slots:
    void readyRead();
    void send_msg(QByteArray msg);
};
