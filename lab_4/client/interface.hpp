#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QJsonObject>

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

signals:
    void request(QJsonObject json_request);

public slots:
    void ans(QJsonObject json_answer) const;

private slots:
    void send_x_val();
    void send_coeffs();
    void RequestForm();

private:
    struct rational {
      int numerator;
      int denumerator;
    };

    std::array<rational, count_coeffs> coeffs = {
        rational{1, 1}, rational{1, 1}, rational{1, 1}
    };

    QJsonObject rationalToJson(const rational& coeff) const;

    rational x{1, 1};
};
