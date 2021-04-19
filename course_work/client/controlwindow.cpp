#include "controlwindow.hpp"

#include <QSizePolicy>

ControlWindow::ControlWindow(QWidget* parent)
    : QWidget(parent),
      hbox_ptr(new QHBoxLayout),
      vbox_ptr(new QVBoxLayout),
      grid_form_ptr(new QGridLayout(this))
{
    //vbox_ptr->setSpacing(100);

    grid_form_ptr->setVerticalSpacing(15);
    grid_form_ptr->setHorizontalSpacing(10);
    title_label_ptr = std::make_unique<QLabel>("Request", this);
    title_label_ptr->setStyleSheet("QLabel {font: 16pt;}");
    name_label_ptr = std::make_unique<QLabel>("Name", this);
    email_label_ptr = std::make_unique<QLabel>("Email", this);
    descript_label_ptr = std::make_unique<QLabel>("Description", this);
    name_edit_ptr = std::make_unique<QLineEdit>(this);
    email_edit_ptr = std::make_unique<QLineEdit>(this);
    descript_edit_ptr = std::make_unique<QTextEdit>(this);

    name_label_ptr->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    email_label_ptr->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    descript_label_ptr->setAlignment(Qt::AlignRight | Qt::AlignTop);

    grid_form_ptr->addWidget(title_label_ptr.get(), 0, 0, 1, 1);
    grid_form_ptr->addWidget(name_label_ptr.get(), 1, 0, 1, 1);
    grid_form_ptr->addWidget(name_edit_ptr.get(), 1, 1, 1, 1);
    grid_form_ptr->addWidget(email_label_ptr.get(), 2, 0, 1, 1);
    grid_form_ptr->addWidget(email_edit_ptr.get(), 2, 1, 1, 1);
    grid_form_ptr->addWidget(descript_label_ptr.get(), 3, 0, 1, 1);
    grid_form_ptr->addWidget(descript_edit_ptr.get(), 3, 1, 4, 1);



    vbox_ptr->addLayout(grid_form_ptr.get());


    setLayout(vbox_ptr.get());
}
