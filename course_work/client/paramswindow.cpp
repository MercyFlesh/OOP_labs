#include "paramswindow.hpp"


ParamsWindow::ParamsWindow(QWidget* parent)
    : QWidget(parent), notice(new Notice),
      vbox_layout(new QVBoxLayout(this)),
      add_form_layout(new QFormLayout),
      update_form_layout(new QFormLayout),
      delete_form_layout(new QFormLayout)
{
    add_manager_label = std::make_unique<QLabel>("Add manager", this);
    add_manager_name_edit = std::make_unique<QLineEdit>(this);
    add_manager_rating_edit = std::make_unique<QLineEdit>(this);
    add_manager_btn = std::make_unique<QPushButton>("add", this);

    update_manager_label = std::make_unique<QLabel>("Update rating", this);
    id_update_manager_edit = std::make_unique<QLineEdit>(this);
    update_rating = std::make_unique<QLineEdit>(this);
    update_manager_btn = std::make_unique<QPushButton>("update", this);

    delete_manager_label = std::make_unique<QLabel>("Delete manager", this);
    delete_id_manager_edit = std::make_unique<QLineEdit>(this);
    delete_manager_btn = std::make_unique<QPushButton>("delete", this);

    add_manager_label->setStyleSheet("QLabel {font: 14pt;}");
    update_manager_label->setStyleSheet("QLabel {font: 14pt;}");
    delete_manager_label->setStyleSheet("QLabel {font: 14pt;}");

    add_manager_name_edit->setMaximumWidth(150);
    add_manager_rating_edit->setMaximumWidth(150);
    add_manager_btn->setMaximumWidth(60);

    id_update_manager_edit->setMaximumWidth(150);
    update_rating->setMaximumWidth(150);
    update_manager_btn->setMaximumWidth(60);

    delete_id_manager_edit->setMaximumWidth(150);
    delete_manager_btn->setMaximumWidth(60);

    add_form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    update_form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    delete_form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    add_form_layout->addRow("Name", add_manager_name_edit.get());
    add_form_layout->addRow("Rating", add_manager_rating_edit.get());
    add_form_layout->addWidget(add_manager_btn.get());

    update_form_layout->addRow("id", id_update_manager_edit.get());
    update_form_layout->addRow("Rating", update_rating.get());
    update_form_layout->addWidget(update_manager_btn.get());

    delete_form_layout->addWidget(delete_manager_label.get());
    delete_form_layout->addWidget(delete_manager_label.get());
    delete_form_layout->addRow("id", delete_id_manager_edit.get());
    delete_form_layout->addWidget(delete_manager_btn.get());

    vbox_layout->setSizeConstraint(QLayout::SetFixedSize);
    vbox_layout->setSpacing(10);

    vbox_layout->addWidget(add_manager_label.get());
    vbox_layout->addLayout(add_form_layout.get());
    vbox_layout->addWidget(update_manager_label.get());
    vbox_layout->addLayout(update_form_layout.get());
    vbox_layout->addLayout(delete_form_layout.get());

    setLayout(vbox_layout.get());

    connect(add_manager_btn.get(), SIGNAL(pressed()), this, SLOT(validate_add_params()));
    connect(update_manager_btn.get(), SIGNAL(pressed()), this, SLOT(validate_update_params()));
    connect(delete_manager_btn.get(), SIGNAL(pressed()), this, SLOT(validate_delete_params()));
}


void ParamsWindow::update_params(QJsonObject response)
{
    if (response["action"].toString() == "new_manager")
    {
        add_manager_name_edit->clear();
        add_manager_rating_edit->clear();

        notice->setProperties(QColor(23, 235, 143, 180), "Succes");
    }
    else if (response["action"].toString() == "update_succes")
    {
        id_update_manager_edit->clear();
        update_rating->clear();

        notice->setProperties(QColor(23, 235, 143, 180), "Succes");
    }
    else if (response["action"].toString() == "update_fail")
    {
        id_update_manager_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
        update_rating->clear();

        notice->setProperties(QColor(249, 93, 119, 180), "Fail");
    }
    else if (response["action"].toString() == "delete_succes")
    {
        delete_id_manager_edit->clear();
        notice->setProperties(QColor(23, 235, 143, 180), "Succes");
    }
    else if (response["action"].toString() == "delete_fail")
    {
        delete_id_manager_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
        notice->setProperties(QColor(249, 93, 119, 180), "Fail");
    }

    notice->show();
}


void ParamsWindow::validate_add_params()
{
    if (!add_manager_name_edit->text().isEmpty() &&
        !add_manager_rating_edit->text().isEmpty())
    {
        add_manager_name_edit->setStyleSheet("");
        add_manager_rating_edit->setStyleSheet("");

        send_add_form();
        return;
    }

    if (add_manager_name_edit->text().isEmpty())
    {
        add_manager_name_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
    else
    {
        add_manager_name_edit->setStyleSheet("");
    }

    if (add_manager_rating_edit->text().isEmpty())
    {
        add_manager_rating_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
    else
    {
        add_manager_rating_edit->setStyleSheet("");
    }
}


void ParamsWindow::validate_update_params()
{
    if (!id_update_manager_edit->text().isEmpty() &&
        !update_rating->text().isEmpty())
    {
        id_update_manager_edit->setStyleSheet("");
        update_rating->setStyleSheet("");

        send_update_form();
        return;
    }

    if (id_update_manager_edit->text().isEmpty())
    {
        id_update_manager_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
    else
    {
        id_update_manager_edit->setStyleSheet("");
    }

    if (update_rating->text().isEmpty())
    {
        update_rating->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
    else
    {
        update_rating->setStyleSheet("");
    }
}


void ParamsWindow::validate_delete_params()
{
    if (!delete_id_manager_edit->text().isEmpty())
    {
        delete_id_manager_edit->setStyleSheet("");

        send_delete_form();
    }
    else
    {
        delete_id_manager_edit->setStyleSheet("QLineEdit {border: 1px solid #B9103C}");
    }
}


void ParamsWindow::send_add_form()
{
    QJsonObject json_request{{"type", "params"}};
    json_request.insert("action", "add_manager");
    json_request.insert("name", add_manager_name_edit->text());
    json_request.insert("rating", add_manager_rating_edit->text().toInt());

    emit send_params_req(json_request);
}


void ParamsWindow::send_update_form()
{
    QJsonObject json_request{{"type", "params"}};
    json_request.insert("action", "update_rating");
    json_request.insert("id", id_update_manager_edit->text().toInt());
    json_request.insert("rating", update_rating->text().toInt());

    emit send_params_req(json_request);
}


void ParamsWindow::send_delete_form()
{
    QJsonObject json_request{{"type", "params"}};
    json_request.insert("action", "delete_manager");
    json_request.insert("id", delete_id_manager_edit->text().toInt());

    emit send_params_req(json_request);
}
