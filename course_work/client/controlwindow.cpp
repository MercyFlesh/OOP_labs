#include "controlwindow.hpp"

#include <QJsonObject>
#include <QJsonDocument>

ControlWindow::ControlWindow(QWidget* parent)
    : QWidget(parent),
      hbox_ptr(new QHBoxLayout),
      vbox_ptr(new QVBoxLayout),
      grid_form_ptr(new QGridLayout(this))
{
    grid_form_ptr->setVerticalSpacing(15);
    grid_form_ptr->setHorizontalSpacing(10);

    title_label_ptr = std::make_unique<QLabel>("Request", this);
    title_label_ptr->setStyleSheet("QLabel {font: 16pt;}");

    request_number_ptr = std::make_unique<QLineEdit>("#", this);
    request_number_ptr->setReadOnly(true);

    name_label_ptr = std::make_unique<QLabel>("Name", this);
    email_label_ptr = std::make_unique<QLabel>("Email", this);
    descript_label_ptr = std::make_unique<QLabel>("Description", this);
    name_edit_ptr = std::make_unique<QLineEdit>(this);
    email_edit_ptr = std::make_unique<QLineEdit>(this);
    descript_edit_ptr = std::make_unique<QTextEdit>(this);

    send_btn_ptr = std::make_unique<QPushButton>("send", this);

    name_label_ptr->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    email_label_ptr->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    descript_label_ptr->setAlignment(Qt::AlignRight | Qt::AlignTop);

    grid_form_ptr->addWidget(title_label_ptr.get(), 0, 0, 1, 1);
    grid_form_ptr->addWidget(request_number_ptr.get(), 1, 1, 1, 2);
    grid_form_ptr->addWidget(name_label_ptr.get(), 2, 0, 1, 1);
    grid_form_ptr->addWidget(name_edit_ptr.get(), 2, 1, 1, 2);
    grid_form_ptr->addWidget(email_label_ptr.get(), 3, 0, 1, 1);
    grid_form_ptr->addWidget(email_edit_ptr.get(), 3, 1, 1, 2);
    grid_form_ptr->addWidget(descript_label_ptr.get(), 4, 0, 1, 1);
    grid_form_ptr->addWidget(descript_edit_ptr.get(), 4, 1, 1, 2);
    grid_form_ptr->addWidget(send_btn_ptr.get(), 5, 2, 1, 1);

    vbox_ptr->addLayout(grid_form_ptr.get());
    setLayout(vbox_ptr.get());

    connect(send_btn_ptr.get(), SIGNAL(pressed()), this, SLOT(validate_form()));
    connect(this, SIGNAL(isValid()), this, SLOT(send_request()));
    connect(this, SIGNAL(control_response(QJsonObject)), this, SLOT(print_request_number(QJsonObject)));
}


void ControlWindow::validate_form()
{
    if (!name_edit_ptr->text().isEmpty() &&
        !email_edit_ptr->text().isEmpty() &&
        !descript_edit_ptr->toPlainText().isEmpty())
    {
        name_edit_ptr->setStyleSheet("");
        email_edit_ptr->setStyleSheet("");
        descript_edit_ptr->setStyleSheet("");

        emit isValid();
        return;
    }

    if (name_edit_ptr->text().isEmpty())
    {
        name_edit_ptr->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
    else
    {
        name_edit_ptr->setStyleSheet("");
    }

    if (email_edit_ptr->text().isEmpty())
    {
        email_edit_ptr->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
    else
    {
        email_edit_ptr->setStyleSheet("");
    }

    if (descript_edit_ptr->toPlainText().isEmpty())
    {
        descript_edit_ptr->setStyleSheet("QTextEdit {border: 1px solid #B9103C}");
    }
    else
    {
        descript_edit_ptr->setStyleSheet("");
    }
}


void ControlWindow::send_request()
{
    QJsonObject json_request;

    json_request.insert("name", name_edit_ptr->text());
    json_request.insert("email", email_edit_ptr->text());
    json_request.insert("description", descript_edit_ptr->toPlainText());

    emit send_control_req(json_request);
}


void ControlWindow::print_request_number(QJsonObject response)
{
    request_number_ptr->setText("#" + response.value("number").toString());
    request_number_ptr->setStyleSheet("QLineEdit {border: 1px solid #1AD39A}");

    name_edit_ptr->clear();
    email_edit_ptr->clear();
    descript_edit_ptr->clear();
}
