#pragma once

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QJsonObject>

#include <memory>

#include "notice.hpp"

class ControlWindow : public QWidget
{
    Q_OBJECT

    std::unique_ptr<QLabel> add_title_label, del_title_label;
    std::unique_ptr<QLineEdit> add_request_id_edit, del_request_id_edit;
    std::unique_ptr<QLineEdit> name_edit, email_edit;
    std::unique_ptr<QTextEdit> descript_edit;

    std::unique_ptr<QPushButton> add_send_btn, del_send_btn;

    std::unique_ptr<QLabel> complete_task_label;
    std::unique_ptr<QLineEdit> complete_id_task_edit;
    std::unique_ptr<QPushButton> complete_task_btn;

    std::unique_ptr<QVBoxLayout> vbox_layout;
    std::unique_ptr<QFormLayout> add_form_layout, del_from_layout, complete_form_layout;

    std::unique_ptr<Notice> notice;

public:
    explicit ControlWindow(QWidget* parent = nullptr);
    ~ControlWindow() = default;

    void update_control(QJsonObject response);

public slots:
    void validate_form();
    void send_request();
    void delete_request();
    void complete_request();

signals:
    void send_control_req(QJsonObject request);
};
