#pragma once

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include <memory>

class ControlWindow : public QWidget
{
    Q_OBJECT

    std::unique_ptr<QLabel> title_label_ptr, name_label_ptr;
    std::unique_ptr<QLabel> email_label_ptr, descript_label_ptr;
    std::unique_ptr<QLineEdit> name_edit_ptr, email_edit_ptr;
    std::unique_ptr<QTextEdit> descript_edit_ptr;

    std::unique_ptr<QGridLayout> grid_form_ptr;
    std::unique_ptr<QHBoxLayout> hbox_ptr;
    std::unique_ptr<QVBoxLayout> vbox_ptr;
public:
    explicit ControlWindow(QWidget* parent = nullptr);
    ~ControlWindow() = default;
};
