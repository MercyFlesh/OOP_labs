#pragma once

#include <QObject>
#include <QJsonObject>
#include <QCoreApplication>
#include <memory>

#include "../common/communicator.hpp"
#include "rational.hpp"

class App : public QCoreApplication
{
    Q_OBJECT

    std::unique_ptr<Communicator> com_ptr;

public:
    App(int argc, char* argv[]);

private:
    Rational toRational(QJsonObject coeff);

    template<typename number>
    void make_response(QJsonObject json_request,
                       number a, number b, number c, std::optional<number> x);

public slots:
    void rec(QByteArray request);
};
