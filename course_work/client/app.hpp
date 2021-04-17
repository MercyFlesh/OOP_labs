#pragma once

#include <QObject>
#include <QApplication>
#include <QJsonObject>
#include <QScopedPointer>

#include "interface.hpp"
#include "client.hpp"


class App : public QApplication
{
    Q_OBJECT

    QScopedPointer<Interface> interface_ptr;
    QScopedPointer<Client> client_ptr;

public:
    explicit App(int argc, char* argv[]);
    ~App() = default;

public slots:
    //void send(QJsonObject json_msg);
    //void accept();
};
