#pragma once

#include <QObject>
#include <QWidget>

class ControlWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget* parent = nullptr);
    ~ControlWindow() = default;
};
