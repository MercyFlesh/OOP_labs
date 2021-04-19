#include "app.hpp"


App::App(int argc, char* argv[])
    : QApplication(argc, argv),
      interface_ptr(new Interface),
      client_ptr(new Client(QHostAddress::LocalHost, 5000))
{
    interface_ptr->show();

    connect(this, SIGNAL(send_control_req(QJsonObject)), this, SLOT(send(QJsonObject)));
}


void App::send(QJsonObject json_msg)
{
    QJsonDocument jsonDoc_ans;
    jsonDoc_ans.setObject(json_msg);
    QByteArray dataArray = jsonDoc_ans.toJson();

    client_ptr->send_data(dataArray);
}
