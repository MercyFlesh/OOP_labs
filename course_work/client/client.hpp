#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QScopedPointer>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject* parent = nullptr);
    ~Client() = default;

signals:

public slots:
    void conn();
    void disc();
    void readyRead();

private:
    QScopedPointer<QTcpSocket> socket_ptr;
};
