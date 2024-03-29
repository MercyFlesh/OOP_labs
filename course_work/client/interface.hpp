#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QScopedPointer>
#include <QPushButton>

#include "controlwindow.hpp"
#include "statewindow.hpp"
#include "paramswindow.hpp"


class Interface : public QTabWidget
{
    Q_OBJECT

    QScopedPointer<ParamsWindow> params_window_ptr;
    QScopedPointer<StateWindow> state_window_ptr;
    QScopedPointer<ControlWindow> control_window_ptr;

public:
    explicit Interface(QWidget* parent = nullptr);
    ~Interface() = default;

    void update_tabs(QJsonObject response);

signals:
    void send_data(QJsonObject);

public slots:
    void transfer_inf(QJsonObject data);
};
