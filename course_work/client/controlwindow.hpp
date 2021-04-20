#pragma once

#include <QObject>
#include <QWidget>
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

    std::unique_ptr<QLabel> title_label_ptr, name_label_ptr;
    std::unique_ptr<QLabel> email_label_ptr, descript_label_ptr;
    std::unique_ptr<QLineEdit> request_number_ptr;
    std::unique_ptr<QLineEdit> name_edit_ptr, email_edit_ptr;
    std::unique_ptr<QTextEdit> descript_edit_ptr;

    std::unique_ptr<QPushButton> send_btn_ptr;

    std::unique_ptr<QGridLayout> grid_layout_ptr;

public:
    explicit ControlWindow(QWidget* parent = nullptr);
    ~ControlWindow() = default;

    void update_control(QJsonObject response);

private slots:
    void validate_form();
    void send_request();

signals:
    void isValid();
    void send_control_req(QJsonObject request);
};
