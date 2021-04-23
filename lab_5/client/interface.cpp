#include "interface.hpp"

#include <string>


Interface::Interface(QWidget* parent)
    : QWidget(parent),
      vbox_main_layout(new QVBoxLayout(this)),
      hbox_radio_layout(new QHBoxLayout),
      coeffs_form_layout(new QFormLayout),
      hbox_layout(new QHBoxLayout),
      vbox_btns_layout(new QVBoxLayout)
{
    setWindowTitle("work #5");
    setFixedSize(320, 350);

    integer_radio_btn = std::make_unique<QRadioButton>("int", this);
    real_radio_btn = std::make_unique<QRadioButton>("real", this);

    hbox_radio_layout->setSpacing(15);
    hbox_radio_layout->addWidget(integer_radio_btn.get(), 0);
    hbox_radio_layout->addWidget(real_radio_btn.get(), 1, Qt::AlignLeft);

    coeffs_form_layout->setSpacing(15);
    for (std::size_t i = 0; i < count_coeffs; ++i)
    {
        hbox_coeffs_layouts[i] = std::make_unique<QHBoxLayout>();

        nums[i] = std::make_unique<QLineEdit>("1", this);
        delimetrs[i] = std::make_unique<QLabel>("/", this);
        denums[i] = std::make_unique<QLineEdit>("1", this);

        hbox_coeffs_layouts[i]->addWidget(nums[i].get(), 0);
        hbox_coeffs_layouts[i]->addWidget(delimetrs[i].get(), 0);
        hbox_coeffs_layouts[i]->addWidget(denums[i].get(), 1, Qt::AlignLeft);

        coeffs_form_layout->addRow(
                    QString((std::string(1, 'a' + i) + " = ").c_str()),
                    hbox_coeffs_layouts[i].get());

    }

    send_coef_btn = std::make_unique<QPushButton>("send coeffs", this);

    x_num = std::make_unique<QLineEdit>("1", this);
    x_delimetr = std::make_unique<QLabel>("/", this);
    x_denum = std::make_unique<QLineEdit>("1", this);
    send_x_btn = std::make_unique<QPushButton>("send x", this);

    send_coef_btn->setMaximumWidth(150);
    send_x_btn->setMaximumWidth(150);

    hbox_coeffs_layouts[3] = std::make_unique<QHBoxLayout>();
    hbox_coeffs_layouts[3]->addWidget(x_num.get(), 0);
    hbox_coeffs_layouts[3]->addWidget(x_delimetr.get(), 0);
    hbox_coeffs_layouts[3]->addWidget(x_denum.get(), 1, Qt::AlignLeft);

    coeffs_form_layout->addWidget(send_coef_btn.get());
    coeffs_form_layout->addRow("x = ", hbox_coeffs_layouts[3].get());
    coeffs_form_layout->addWidget(send_x_btn.get());

    val_btn = std::make_unique<QPushButton>("value", this);
    root_btn = std::make_unique<QPushButton>("roots", this);
    classic_btn = std::make_unique<QPushButton>("classic", this);
    cannonic_btn = std::make_unique<QPushButton>("cannonic", this);

    vbox_btns_layout->setSpacing(1);
    vbox_btns_layout->addWidget(val_btn.get());
    vbox_btns_layout->addWidget(root_btn.get());
    vbox_btns_layout->addWidget(classic_btn.get());
    vbox_btns_layout->addWidget(cannonic_btn.get());

    hbox_layout->setSpacing(40);
    hbox_layout->addLayout(coeffs_form_layout.get());
    hbox_layout->addLayout(vbox_btns_layout.get(), 0);

    output = std::make_unique<QLabel>(this);
    output->setStyleSheet("QLabel {"
                          "margin-top: 30px;"
                          "padding: 5px, 5px;"
                          "border-style: solid;"
                          "border-width: 1px;"
                          "border-color: black;"
                          "}");

    vbox_main_layout->addLayout(hbox_radio_layout.get());
    vbox_main_layout->addLayout(hbox_layout.get());
    vbox_main_layout->addWidget(output.get());
    setLayout(vbox_main_layout.get());

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
        json_coeffs.insert("x", rationalToJson(x));
        json_request.insert("type", "value");
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

    emit request(json_request);
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
             json_ans["type"].toString() == "canonic")
    {
        output->setText(json_ans["polynom"].toString());
    }
}
