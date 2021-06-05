#pragma once

#include <QObject>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>

#include "server.hpp"
#include "model.hpp"


class App : public QCoreApplication
{
    Q_OBJECT

public:
    explicit App(int argc, char* argv[]);

public slots:
    void rec(int client_index, QByteArray request);

private:
    void make_response(int client_index, QJsonObject jsonObj);

private:
    std::unique_ptr<Server> server;
    std::shared_ptr<Model> model;
};
