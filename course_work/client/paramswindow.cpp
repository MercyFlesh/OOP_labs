#include "paramswindow.hpp"


ParamsWindow::ParamsWindow(QWidget* parent)
    : QWidget(parent),
      vbox_layout(new QVBoxLayout(this)),
      add_form_layout(new QFormLayout()),
      update_form_layout(new QFormLayout())
{
    add_manager_label = std::make_unique<QLabel>("Add manager", this);
    add_manager_name_edit = std::make_unique<QLineEdit>(this);
    add_manager_rating_edit = std::make_unique<QLineEdit>(this);
    add_manager_btn = std::make_unique<QPushButton>("add", this);

    update_manager_label = std::make_unique<QLabel>("Update rating", this);
    id_update_manager_edit = std::make_unique<QLineEdit>(this);
    update_rating = std::make_unique<QLineEdit>(this);
    update_manager_btn = std::make_unique<QPushButton>("update", this);

    add_manager_label->setStyleSheet("QLabel {font: 14pt;}");
    update_manager_label->setStyleSheet("QLabel {font: 14pt;}");
    add_manager_name_edit->setMaximumWidth(150);
    add_manager_rating_edit->setMaximumWidth(150);
    add_manager_btn->setMaximumWidth(60);

    id_update_manager_edit->setMaximumWidth(150);
    update_rating->setMaximumWidth(150);
    update_manager_btn->setMaximumWidth(60);

    add_form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
    update_form_layout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);

    add_form_layout->addRow("Name", add_manager_name_edit.get());
    add_form_layout->addRow("Rating", add_manager_rating_edit.get());
    add_form_layout->addWidget(add_manager_btn.get());

    update_form_layout->addRow("id", id_update_manager_edit.get());
    update_form_layout->addRow("Rating", update_rating.get());
    update_form_layout->addWidget(update_manager_btn.get());

    vbox_layout->setSizeConstraint(QLayout::SetFixedSize);
    vbox_layout->setSpacing(10);

    vbox_layout->addWidget(add_manager_label.get());
    vbox_layout->addLayout(add_form_layout.get());
    vbox_layout->addWidget(update_manager_label.get());
    vbox_layout->addLayout(update_form_layout.get());

    setLayout(vbox_layout.get());
}
