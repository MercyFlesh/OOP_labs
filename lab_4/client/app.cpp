#include "app.hpp"

App::App(int argc, char* argv[])
    : QApplication(argc, argv),
      com_ptr(new Communicator(QHostAddress::LocalHost, 5000)),
      interface_ptr(new Interface)
{
    interface_ptr->show();

    connect(com_ptr.get(), SIGNAL(rec(QByteArray msg)), this, SLOT(acccept(QByteArray msg)));
    connect(com_ptr.get(), SIGNAL(request(Qstring req_msg)), this, SLOT(send(QByteArray msg)));
}


void App::accept(QByteArray msg_ans)
{
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
