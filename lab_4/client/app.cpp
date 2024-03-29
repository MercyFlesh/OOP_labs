#include "app.hpp"

App::App(int argc, char* argv[])
    : QApplication(argc, argv),
      com_ptr(new Communicator(QHostAddress::LocalHost, 5001,
                               QHostAddress::LocalHost, 5000)),
      interface_ptr(new Interface)
{
    interface_ptr->show();

    connect(com_ptr.get(), SIGNAL(rec(QByteArray)), this, SLOT(accept(QByteArray)));
    connect(interface_ptr.get(), SIGNAL(request(QJsonObject)), this, SLOT(send(QJsonObject)));
}


void App::accept(QByteArray msg_ans)
{
    qDebug() << 6;
    QJsonParseError json_error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(msg_ans, &json_error);
    if (json_error.error!= QJsonParseError::NoError)
    {
        qDebug() << "json error";
        return;
    }

    interface_ptr->ans(jsonDoc.object());
}

void App::send(QJsonObject json_request)
{
    QJsonDocument jsonDoc_ans;
    jsonDoc_ans.setObject(json_request);
    QByteArray dataArray = jsonDoc_ans.toJson();

    com_ptr->send_msg(dataArray);
}
