#include "controlwindow.hpp"

#include <QJsonObject>
#include <QJsonDocument>


ControlWindow::ControlWindow(QWidget* parent)
    : QWidget(parent),
      vbox_layout(new QVBoxLayout(this)),
      add_form_layout(new QFormLayout),
      del_from_layout(new QFormLayout),
      complete_form_layout(new QFormLayout),
      notice(new Notice)
{
    //setMinimumSize(500, 600);
    add_title_label = std::make_unique<QLabel>("Add request", this);
    add_title_label->setStyleSheet("QLabel {font: 14pt;}");

    add_request_id_edit = std::make_unique<QLineEdit>(this);
    add_request_id_edit->setReadOnly(true);

    name_edit = std::make_unique<QLineEdit>(this);
    email_edit = std::make_unique<QLineEdit>(this);
    descript_edit = std::make_unique<QTextEdit>(this);
    add_send_btn = std::make_unique<QPushButton>("add", this);

    complete_task_label = std::make_unique<QLabel>("Complete request", this);
    complete_task_label->setStyleSheet("QLabel {font: 14pt;}");
    complete_id_task_edit = std::make_unique<QLineEdit>(this);
    complete_task_btn = std::make_unique<QPushButton>("complete", this);

    del_title_label = std::make_unique<QLabel>("Delete request", this);
    del_title_label->setStyleSheet("QLabel {font: 14pt;}");
    del_request_id_edit = std::make_unique<QLineEdit>(this);
    del_send_btn = std::make_unique<QPushButton>("delete", this);

    add_request_id_edit->setMaximumWidth(200);
    name_edit->setMaximumWidth(200);
    email_edit->setMaximumWidth(200);
    descript_edit->setMaximumSize(200, 150);
    add_send_btn->setMaximumWidth(60);

    complete_id_task_edit->setMaximumWidth(200);
    complete_task_btn->setMaximumWidth(60);

    del_request_id_edit->setMaximumWidth(200);
    del_send_btn->setMaximumWidth(60);

    add_form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    complete_form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    del_from_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    add_form_layout->addRow("name", name_edit.get());
    add_form_layout->addRow("email", email_edit.get());
    add_form_layout->addRow("descript", descript_edit.get());
    add_form_layout->addRow("task id", add_request_id_edit.get());
    add_form_layout->addWidget(add_send_btn.get());

    complete_form_layout->addRow("task id", complete_id_task_edit.get());
    complete_form_layout->addWidget(complete_task_btn.get());

    del_from_layout->addRow("task id", del_request_id_edit.get());
    del_from_layout->addWidget(del_send_btn.get());

    vbox_layout->setSpacing(10);
    vbox_layout->setSizeConstraint(QLayout::SetFixedSize);
    vbox_layout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    vbox_layout->addWidget(add_title_label.get());
    vbox_layout->addLayout(add_form_layout.get());
    vbox_layout->addWidget(complete_task_label.get());
    vbox_layout->addLayout(complete_form_layout.get());
    vbox_layout->addWidget(del_title_label.get());
    vbox_layout->addLayout(del_from_layout.get());

    setLayout(vbox_layout.get());

    connect(add_send_btn.get(), SIGNAL(pressed()), this, SLOT(validate_form()));
    connect(complete_task_btn.get(), SIGNAL(pressed()), this, SLOT(complete_request()));
    connect(del_send_btn.get(), SIGNAL(pressed()), this, SLOT(delete_request()));
}


void ControlWindow::validate_form()
{
    if (!name_edit->text().isEmpty() &&
        !email_edit->text().isEmpty() &&
        !descript_edit->toPlainText().isEmpty())
    {
        name_edit->setStyleSheet("");
        email_edit->setStyleSheet("");
        descript_edit->setStyleSheet("");

        send_request();
        return;
    }

    if (name_edit->text().isEmpty())
    {
        name_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
    else
    {
        name_edit->setStyleSheet("");
    }

    if (email_edit->text().isEmpty())
    {
        email_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
    else
    {
        email_edit->setStyleSheet("");
    }

    if (descript_edit->toPlainText().isEmpty())
    {
        descript_edit->setStyleSheet("QTextEdit {border: 1px solid #B9103C}");
    }
    else
    {
        descript_edit->setStyleSheet("");
    }
}


void ControlWindow::send_request()
{
    QJsonObject json_request;

    json_request.insert("type", "control");
    json_request.insert("action", "add_request");
    json_request.insert("name", name_edit->text());
    json_request.insert("email", email_edit->text());
    json_request.insert("description", descript_edit->toPlainText());

    emit send_control_req(json_request);
}


void ControlWindow::delete_request()
{
    if (!del_request_id_edit->text().isEmpty())
    {
        del_request_id_edit->setStyleSheet("");

        QJsonObject json_request;
        json_request.insert("type", "control");
        json_request.insert("action", "del_request");
        json_request.insert("id_request", del_request_id_edit->text().toInt());

        emit send_control_req(json_request);
    }
    else
    {
        del_request_id_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
}


void ControlWindow::complete_request()
{
    if (!complete_id_task_edit->text().isEmpty())
    {
        complete_id_task_edit->setStyleSheet("");

        QJsonObject json_request;
        json_request.insert("type", "control");
        json_request.insert("action", "complete_request");
        json_request.insert("id_request", complete_id_task_edit->text().toInt());

        emit send_control_req(json_request);
    }
    else
    {
        complete_id_task_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
}


void ControlWindow::update_control(QJsonObject response)
{
    if (response["action"].toString() == "new_request")
    {
        add_request_id_edit->setText(QString().number(response.value("id").toInt()));
        add_request_id_edit->setStyleSheet("QLineEdit {border: 1px solid #1AD39A}");

        name_edit->clear();
        email_edit->clear();
        descript_edit->clear();

        notice->setProperties(QColor(23, 235, 143, 180), "Succes");
    }
    else if (response["action"].toString() == "del_succes")
    {
        del_request_id_edit->clear();
        notice->setProperties(QColor(23, 235, 143, 180), "Succes");
    }
    else if (response["action"].toString() == "del_fail")
    {
        del_request_id_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
        notice->setProperties(QColor(249, 93, 119, 180), "Fail");
    }
    else if (response["action"].toString() == "complete_succes")
    {
        complete_id_task_edit->clear();
        notice->setProperties(QColor(23, 235, 143, 180), "Succes");
    }
    else if (response["action"].toString() == "complete_fail")
    {
        complete_id_task_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
        notice->setProperties(QColor(249, 93, 119, 180), "Fail");
    }

    notice->show();
}
