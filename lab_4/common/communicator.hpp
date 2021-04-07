#pragma once

#include <QObject>
#include <QUdpSocket>

class Communicator : public QUdpSocket
{
    Q_OBJECT

    QHostAddress host_;
    quint16 port_;

public:
    explicit Communicator(QHostAddress host,
                          quint16 port,
                          QObject* parent = nullptr);

signals:
    void rec(QByteArray msg);

public slots:
    void readyRead();
    void send_msg(QByteArray msg);
};
