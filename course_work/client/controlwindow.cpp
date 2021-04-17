#include "controlwindow.hpp"

ControlWindow::ControlWindow(QWidget* parent)
    : QWidget(parent),
      hbox_ptr(new QHBoxLayout),
      grid_form_ptr(new QGridLayout(this))
{
    grid_form_ptr->setVerticalSpacing(15);
    grid_form_ptr->setHorizontalSpacing(10);

    name_label_ptr = std::make_unique<QLabel>("Name", this);
    email_label_ptr = std::make_unique<QLabel>("Email", this);
    descript_label_ptr = std::make_unique<QLabel>("Description", this);
    name_edit_ptr = std::make_unique<QLineEdit>(this);
    email_edit_ptr = std::make_unique<QLineEdit>(this);
    descript_edit_ptr = std::make_unique<QTextEdit>(this);

    grid_form_ptr->addWidget(name_label_ptr.get(), 0, 0, 1, 1);
    grid_form_ptr->addWidget(name_edit_ptr.get(), 0, 1, 1, 1);
    grid_form_ptr->addWidget(email_label_ptr.get(), 1, 0, 1, 1);
    grid_form_ptr->addWidget(email_edit_ptr.get(), 1, 1, 1, 1);
    grid_form_ptr->addWidget(descript_label_ptr.get(), 2, 0, 1, 1);
    grid_form_ptr->addWidget(descript_edit_ptr.get(), 2, 1, 4, 1);

    setLayout(grid_form_ptr.get());
}
