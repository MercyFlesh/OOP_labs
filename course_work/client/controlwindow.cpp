#include "controlwindow.hpp"

#include <QJsonObject>
#include <QJsonDocument>


ControlWindow::ControlWindow(QWidget* parent)
    : QWidget(parent),
      vbox_layout(new QVBoxLayout(this)),
      add_form_layout(new QFormLayout),
      del_from_layout(new QFormLayout)
{
    add_title_label = std::make_unique<QLabel>("Add request", this);
    add_title_label->setStyleSheet("QLabel {font: 14pt;}");

    add_request_id_edit = std::make_unique<QLineEdit>(this);
    add_request_id_edit->setReadOnly(true);

    name_edit = std::make_unique<QLineEdit>(this);
    email_edit = std::make_unique<QLineEdit>(this);
    descript_edit = std::make_unique<QTextEdit>(this);
    add_send_btn = std::make_unique<QPushButton>("add", this);

    del_title_label = std::make_unique<QLabel>("Delete request", this);
    del_title_label->setStyleSheet("QLabel {font: 14pt;}");
    del_request_id_edit = std::make_unique<QLineEdit>(this);
    del_send_btn = std::make_unique<QPushButton>("delete", this);

    add_request_id_edit->setMaximumWidth(200);
    name_edit->setMaximumWidth(200);
    email_edit->setMaximumWidth(200);
    descript_edit->setMaximumSize(200, 150);
    add_send_btn->setMaximumWidth(60);

    del_request_id_edit->setMaximumWidth(200);
    del_send_btn->setMaximumWidth(60);

    add_form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    del_from_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    add_form_layout->addRow("name", name_edit.get());
    add_form_layout->addRow("email", email_edit.get());
    add_form_layout->addRow("descript", descript_edit.get());
    add_form_layout->addRow("id", add_request_id_edit.get());
    add_form_layout->addWidget(add_send_btn.get());

    del_from_layout->addRow("id", del_request_id_edit.get());
    del_from_layout->addWidget(del_send_btn.get());

    vbox_layout->setSpacing(10);
    vbox_layout->setSizeConstraint(QLayout::SetFixedSize);
    vbox_layout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    vbox_layout->addWidget(add_title_label.get());
    vbox_layout->addLayout(add_form_layout.get());
    vbox_layout->addWidget(del_title_label.get());
    vbox_layout->addLayout(del_from_layout.get());


    setLayout(vbox_layout.get());

    connect(add_send_btn.get(), SIGNAL(pressed()), this, SLOT(validate_form()));
    connect(del_send_btn.get(), SIGNAL(pressed()), this, SLOT(delete_request()));
    connect(this, SIGNAL(isValid()), this, SLOT(send_request()));
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

        emit isValid();
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

    json_request.insert("type", "control_add");
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
        json_request.insert("type", "control_del");
        json_request.insert("id_requst", del_request_id_edit->text());

        emit send_control_req(json_request);
    }
    else
    {
        del_request_id_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }


}


void ControlWindow::update_control(QJsonObject response)
{
    add_request_id_edit->setText(response.value("number").toString());
    add_request_id_edit->setStyleSheet("QLineEdit {border: 1px solid #1AD39A}");

    name_edit->clear();
    email_edit->clear();
    descript_edit->clear();
}
