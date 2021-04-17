#pragma once

#include <QWidget>
#include <QTabWidget>
#include <QScopedPointer>
#include <QPushButton>
#include <QMainWindow>
#include <QDialog>
#include <QSizePolicy>

#include "controlwindow.hpp"
#include "statewindow.hpp"
#include "paramswindow.hpp"


class Interface : public QMainWindow
{
    Q_OBJECT

    QScopedPointer<QTabWidget> tab_widgets_ptr;
    QScopedPointer<ParamsWindow> params_window_ptr;
    QScopedPointer<StateWindow> state_window_ptr;
    QScopedPointer<ControlWindow> control_window_ptr;

public:
    explicit Interface(QWidget* parent = nullptr);
    ~Interface() = default;

public slots:
};
