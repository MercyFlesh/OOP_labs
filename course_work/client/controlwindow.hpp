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

class ControlWindow : public QWidget
{
    Q_OBJECT

    std::unique_ptr<QLabel> add_title_label, del_title_label;
    std::unique_ptr<QLineEdit> add_request_id_edit, del_request_id_edit;
    std::unique_ptr<QLineEdit> name_edit, email_edit;
    std::unique_ptr<QTextEdit> descript_edit;

    std::unique_ptr<QPushButton> add_send_btn, del_send_btn;

    std::unique_ptr<QVBoxLayout> vbox_layout;
    std::unique_ptr<QFormLayout> add_form_layout, del_from_layout;

public:
    explicit ControlWindow(QWidget* parent = nullptr);
    ~ControlWindow() = default;

    void update_control(QJsonObject response);

private slots:
    void validate_form();
    void send_request();
    void delete_request();

signals:
    void isValid();
    void send_control_req(QJsonObject request);
};
