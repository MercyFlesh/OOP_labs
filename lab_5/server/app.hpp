#pragma once

#include <QObject>
#include <QJsonObject>
#include <QCoreApplication>
#include <memory>

#include "../common/communicator.hpp"
#include "number.hpp"

class App : public QCoreApplication
{
    Q_OBJECT

    std::unique_ptr<Communicator> com_ptr;

public:
    App(int argc, char* argv[]);

private:
    number toRational(QJsonObject coeff);

public slots:
    void rec(QByteArray request);
};
