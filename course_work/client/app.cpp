#include "app.hpp"


App::App(int argc, char* argv[])
    : QApplication(argc, argv),
      interface_ptr(new Interface),
      client_ptr(new Client(QHostAddress::LocalHost, 5000))
{
    interface_ptr->show();

    connect(interface_ptr.get(), SIGNAL(send_data(QJsonObject)), this, SLOT(send(QJsonObject)));
    connect(client_ptr.get(), SIGNAL(accept_response(QByteArray)), this, SLOT(accept(QByteArray)));
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
