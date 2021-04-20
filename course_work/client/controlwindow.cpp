#include "controlwindow.hpp"

#include <QJsonObject>
#include <QJsonDocument>


ControlWindow::ControlWindow(QWidget* parent)
    : QWidget(parent),
      grid_layout(new QGridLayout(this))
{
    grid_layout->setVerticalSpacing(15);
    grid_layout->setHorizontalSpacing(10);

    add_title_label = std::make_unique<QLabel>("Add request", this);
    add_title_label->setStyleSheet("QLabel {font: 14pt;}");

    id_add_request_label = std::make_unique<QLabel>("id", this);
    add_request_number_edit = std::make_unique<QLineEdit>(this);
    add_request_number_edit->setReadOnly(true);

    name_label = std::make_unique<QLabel>("Name", this);
    email_label_ptr = std::make_unique<QLabel>("Email", this);
    descript_label = std::make_unique<QLabel>("Description", this);
    name_edit = std::make_unique<QLineEdit>(this);
    email_edit = std::make_unique<QLineEdit>(this);
    descript_edit = std::make_unique<QTextEdit>(this);

    add_send_btn = std::make_unique<QPushButton>("add", this);

    del_title_label = std::make_unique<QLabel>("Delete request", this);
    del_title_label->setStyleSheet("QLabel {font: 14pt;}");
    id_del_request_label = std::make_unique<QLabel>("id", this);
    del_request_number_edit = std::make_unique<QLineEdit>(this);
    del_send_btn = std::make_unique<QPushButton>("delete", this);

    name_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    email_label_ptr->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    descript_label->setAlignment(Qt::AlignRight | Qt::AlignTop);
    id_del_request_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    id_add_request_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    grid_layout->addWidget(add_title_label.get(), 0, 1, 1, 4);
    grid_layout->addWidget(name_label.get(), 1, 0, 1, 1);
    grid_layout->addWidget(name_edit.get(), 1, 1, 1, 2);
    grid_layout->addWidget(email_label_ptr.get(), 2, 0, 1, 1);
    grid_layout->addWidget(email_edit.get(), 2, 1, 1, 2);
    grid_layout->addWidget(descript_label.get(), 3, 0, 1, 1);
    grid_layout->addWidget(descript_edit.get(), 3, 1, 1, 2);
    grid_layout->addWidget(id_add_request_label.get(), 4, 0, 1, 1);
    grid_layout->addWidget(add_request_number_edit.get(), 4, 1, 1, 2);
    grid_layout->addWidget(add_send_btn.get(), 5, 2, 1, 1);

    grid_layout->addWidget(del_title_label.get(), 6, 1, 1, 1);
    grid_layout->addWidget(id_del_request_label.get(), 7, 0, 1, 1);
    grid_layout->addWidget(del_request_number_edit.get(), 7, 1, 1, 1);
    grid_layout->addWidget(del_send_btn.get(), 7, 2, 1, 1);

    setLayout(grid_layout.get());

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
    if (!del_request_number_edit->text().isEmpty())
    {
        del_request_number_edit->setStyleSheet("");

        QJsonObject json_request;
        json_request.insert("type", "control_del");
        json_request.insert("id_requst", del_request_number_edit->text());

        emit send_control_req(json_request);
    }
    else
    {
        del_request_number_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }


}


void ControlWindow::update_control(QJsonObject response)
{
    add_request_number_edit->setText(response.value("number").toString());
    add_request_number_edit->setStyleSheet("QLineEdit {border: 1px solid #1AD39A}");

    name_edit->clear();
    email_edit->clear();
    descript_edit->clear();
}
