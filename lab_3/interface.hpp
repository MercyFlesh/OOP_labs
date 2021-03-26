#pragma once
#include "number.hpp"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include <memory>
#include <array>

using Label_ptr = std::unique_ptr<QLabel>;
using LineEdit_ptr = std::unique_ptr<QLineEdit>;
using PushButton_ptr = std::unique_ptr<QPushButton>;


class Interface : public QWidget
{
    Q_OBJECT
    static constexpr int count_coeffs = 3;

    std::array<Label_ptr, count_coeffs> names, delimetrs;
    std::array<LineEdit_ptr, count_coeffs> nums;
    std::array<LineEdit_ptr, count_coeffs> denums;

    LineEdit_ptr x_num, x_denum;
    Label_ptr x_name, x_delimetr;

    PushButton_ptr val_btn, root_btn;
    PushButton_ptr classic_btn, cannonic_btn;
    PushButton_ptr send_coef_btn, send_x_btn;

    Label_ptr output;

public:
    Interface(QWidget* parent = nullptr);
    ~Interface() = default;

public slots:
    void send_x_val();
    void print_value() const;
    void print_roots() const;
    void print_classic() const;
    void print_cannonic() const;

private:
    std::array<number, count_coeffs> coeffs = {1, 1, 1};
};
