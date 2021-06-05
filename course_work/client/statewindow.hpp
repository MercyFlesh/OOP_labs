#pragma once
#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <memory>

class StateWindow : public QWidget
{
    Q_OBJECT

    std::unique_ptr<QTableWidget> states_table;
    std::unique_ptr<QPushButton> update_btn;
    std::unique_ptr<QComboBox> states_box;

    std::unique_ptr<QHBoxLayout> hbox_choice_layout;
    std::unique_ptr<QVBoxLayout> main_layout;

public:
    explicit StateWindow(QWidget* parent = nullptr);
    ~StateWindow() = default;

    void update_state(QJsonObject response);

public slots:
    void send_request();

signals:
    void send_state_req(QJsonObject);
};
