#pragma once

#include <QObject>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QScopedPointer>
#include <QByteArray>

#include "interface.hpp"
#include "client.hpp"


class App : public QApplication
{
    Q_OBJECT

    std::unique_ptr<Interface> interface_ptr;
    std::unique_ptr<Client> client_ptr;

public:
    explicit App(int argc, char* argv[]);
    ~App() = default;

public slots:
    void send(QJsonObject json_msg);
    void accept(QByteArray response);
};
