#pragma once
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QJsonObject>
#include <QJsonArray>

#include <memory>

class StateWindow : public QWidget
{
    Q_OBJECT

    std::unique_ptr<QLabel> free_managers_label, busy_managers_label, queue_list_label;
    std::unique_ptr<QListWidget> free_managers_list, busy_managers_list;
    std::unique_ptr<QListWidget> queue_requests_list;
    std::unique_ptr<QPushButton> update_free_btn, update_busy_btn, update_queue_btn;

    std::unique_ptr<QGridLayout> grid_layout;

public:
    explicit StateWindow(QWidget* parent = nullptr);
    ~StateWindow() = default;

    void update_state(QJsonObject response);

public slots:
    void send_request();

signals:
    void send_state_req(QJsonObject);
};
