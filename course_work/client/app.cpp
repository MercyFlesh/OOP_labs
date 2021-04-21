#include "app.hpp"


App::App(int argc, char* argv[])
    : QApplication(argc, argv),
      interface_ptr(new Interface),
      client_ptr(new Client(QHostAddress::LocalHost, 5000))
{
    interface_ptr->show();

    connect(this, SIGNAL(send_control_req(QJsonObject)), this, SLOT(send(QJsonObject)));
    connect(this, SIGNAL(send_state_req(QJsonObject)), this, SLOT(send(QJsonObject)));
    connect(this, SIGNAL(send_params_req(QJsonObject)), this, SLOT(send(QJsonObject)));
    connect(this, SIGNAL(accept_response(QByteArray)), this, SLOT(accept(QByteArray)));
}


void App::send(QJsonObject json_msg)
{
    QJsonDocument jsonDoc_ans;
    jsonDoc_ans.setObject(json_msg);
    QByteArray dataArray = jsonDoc_ans.toJson();

    client_ptr->send_data(dataArray);
}

void App::accept(QByteArray response)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response, &json_error);
    if (json_error.error!= QJsonParseError::NoError)
    {
        qDebug() << "json error";
        return;
     }

     interface_ptr->update_tabs(jsonDoc.object());
}
