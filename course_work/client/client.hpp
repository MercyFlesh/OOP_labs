#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QScopedPointer>
#include <QByteArray>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QHostAddress host, qint16 port,
                    QObject* parent = nullptr);
    ~Client() = default;

public slots:
    void conn();
    void disc();
    void readyRead();
    void send_data(QByteArray data);

signals:
    void accept_response(QByteArray);

private:
    std::unique_ptr<QTcpSocket> socket_ptr;
};
