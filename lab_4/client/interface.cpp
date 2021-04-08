#include "interface.hpp"

#include <string>

Interface::Interface(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("work #3");
    setFixedSize(400, 300);

    for (std::size_t i = 0; i < names.size(); ++i)
    {
        names[i] = std::make_unique<QLabel>(
                    QString((std::string(1, 'a' + i) + " = ").c_str()),
                    this
        );
        nums[i] = std::make_unique<QLineEdit>("1", this);
        delimetrs[i] = std::make_unique<QLabel>("/", this);
        denums[i] = std::make_unique<QLineEdit>("1", this);

        names[i]->setGeometry(10, 20 + (i * 28), 30, 20);
        nums[i]->setGeometry(40, 20 + (i * 28), 30, 20);
        delimetrs[i]->setGeometry(75, 20 + (i * 28), 5, 20);
        denums[i]->setGeometry(85, 20 + (i * 28), 30, 20);
    }

    send_coef_btn = std::make_unique<QPushButton>("send coeffs", this);
    send_coef_btn->setGeometry(10, 25 + (names.size() * 28), 105, 20);

    x_name = std::make_unique<QLabel>("x = ", this);
    x_num = std::make_unique<QLineEdit>("1", this);
    x_delimetr = std::make_unique<QLabel>("/", this);
    x_denum = std::make_unique<QLineEdit>("1", this);

    x_name->setGeometry(10, 35 + ((names.size() + 1) * 28), 30, 20);
    x_num->setGeometry(40, 35 + ((names.size() + 1) * 28), 30, 20);
    x_delimetr->setGeometry(75, 35 + ((names.size() + 1) * 28), 30, 20);
    x_denum->setGeometry(85, 35 + ((names.size() + 1) * 28), 30, 20);

    send_x_btn = std::make_unique<QPushButton>("send x", this);
    send_x_btn->setGeometry(10, 40 + ((names.size() + 2) * 28), 105, 20);

    val_btn = std::make_unique<QPushButton>("value", this);
    root_btn = std::make_unique<QPushButton>("roots", this);
    classic_btn = std::make_unique<QPushButton>("classic", this);
    cannonic_btn = std::make_unique<QPushButton>("cannonic", this);

    val_btn->setGeometry(170, 20, 60, 30);
    root_btn->setGeometry(170, 55, 60, 30);
    classic_btn->setGeometry(170, 90, 60, 30);
    cannonic_btn->setGeometry(170, 125, 60, 30);

    output = std::make_unique<QLabel>(this);
    output->setGeometry(10, 220, 230, 30);
    output->setStyleSheet("QLabel {"
                          "border-style: solid;"
                          "border-width: 1px;"
                          "border-color: black;"
                          "}");

    connect(send_x_btn.get(), SIGNAL(pressed()), this, SLOT(send_x_val()));
    connect(send_coef_btn.get(), SIGNAL(pressed()), this, SLOT(send_coeffs()));
    connect(val_btn.get(), SIGNAL(pressed()), this, SLOT(RequestForm()));
    connect(root_btn.get(), SIGNAL(pressed()), this, SLOT(RequestForm()));
    connect(classic_btn.get(), SIGNAL(pressed()), this, SLOT(RequestForm()));
    connect(cannonic_btn.get(), SIGNAL(pressed()), this, SLOT(RequestForm()));
}


QJsonObject Interface::rationalToJson(const rational& coeff) const
{
    return QJsonObject{
        {"num", coeff.numerator},
        {"denum", coeff.denumerator}
    };
}


void Interface::send_x_val()
{
    if (x_num->isReadOnly())
    {
        x_num->setReadOnly(false);
        x_denum->setReadOnly(false);
    }
    else
    {
        x_num->setReadOnly(true);
        x_denum->setReadOnly(true);

        x = {x_num->text().toInt(), x_denum->text().toInt()};
    }
}


void Interface::send_coeffs()
{
    if (nums[0]->isReadOnly())
    {
        for (std::size_t i = 0; i < nums.size(); ++i)
        {
            nums[i]->setReadOnly(false);
            denums[i]->setReadOnly(false);
        }
    }
    else
    {
        for (std::size_t i = 0; i < nums.size(); ++i)
        {
            nums[i]->setReadOnly(true);
            denums[i]->setReadOnly(true);

            coeffs[i] = {
                nums[i]->text().toInt(),
                denums[i]->text().toInt()
            };
        }
    }
}


void Interface::RequestForm()
{
    QJsonObject json_request;

    QJsonObject json_coeffs{
        {"a", rationalToJson(coeffs[0])},
        {"b", rationalToJson(coeffs[1])},
        {"c", rationalToJson(coeffs[2])},
    };

    QPushButton* btn_ptr = reinterpret_cast<QPushButton*>(sender());
    if (btn_ptr == val_btn.get())
    {
        json_request.insert("type", "value");
        json_coeffs.insert("x", rationalToJson(x));
        json_request.insert("coeffs", json_coeffs);
    }
    else if (btn_ptr == root_btn.get())
    {
        json_request.insert("type", "roots");
        json_request.insert("coeffs", json_coeffs);
    }
    else if (btn_ptr == classic_btn.get())
    {
        json_request.insert("type", "classic");
        json_request.insert("coeffs", json_coeffs);
    }
    else if (btn_ptr == cannonic_btn.get())
    {
        json_request.insert("type", "canonic");
        json_request.insert("coeffs", json_coeffs);
    }

    request(json_request);
}


void Interface::ans(QJsonObject json_ans) const
{
    if (json_ans["type"].toString() == "value")
    {
        output->setText(json_ans["val"].toString());
    }
    else if (json_ans["type"].toString() == "roots")
    {
        QString str_output;
        QString root_1 = json_ans["root_1"].toString();
        QString root_2 = json_ans["root_2"].toString();
        if (root_1 != "" || root_2 != "")
        {
            if (root_1 != "")
                str_output += "x=" + root_1 + "\t";

            if (root_2 != "")
                str_output += "x=" + root_2 + "\t";
        }
        else
            str_output = "[-] no roots in the given field with this coefficints";

        output->setText(str_output);
    }
    else if (json_ans["type"].toString() == "classic" ||
             json_ans["type"].toString() == "cannonic")
    {
        output->setText(json_ans["polynom"].toString());
    }
}
