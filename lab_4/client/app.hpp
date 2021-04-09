#pragma once

#include <QObject>
#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QByteArray>

#include <memory>

#include "interface.hpp"
#include "../common/communicator.hpp"

class App : public QApplication
{
    Q_OBJECT

    std::unique_ptr<Communicator> com_ptr;
    std::unique_ptr<Interface> interface_ptr;

public:
    App(int argc, char* argv[]);

public slots:
    void accept(QByteArray msg);
    void send(QJsonObject request);
};
