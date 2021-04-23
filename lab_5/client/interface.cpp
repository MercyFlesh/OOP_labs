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
    integer_radio_btn->setChecked(true);

    hbox_radio_layout->setSpacing(15);
    hbox_radio_layout->addWidget(integer_radio_btn.get(), 0);
    hbox_radio_layout->addWidget(real_radio_btn.get(), 1, Qt::AlignLeft);

    for (std::size_t i = 0; i < count_coeffs; ++i)
        hbox_coeffs_layouts[i] = std::make_unique<QHBoxLayout>();

    print_inetger_values_form();

    coeffs_form_layout->setSpacing(10);
    coeffs_form_layout->addRow("a = ", hbox_coeffs_layouts[0].get());
    coeffs_form_layout->addRow("b = ", hbox_coeffs_layouts[1].get());
    coeffs_form_layout->addRow("c = ", hbox_coeffs_layouts[2].get());

    send_coef_btn = std::make_unique<QPushButton>("send coeffs", this);
    send_coef_btn->setMaximumWidth(75);
    //send_coef_btn->setStyleSheet("QPushButton {margin-top: -10px;}");
    coeffs_form_layout->addWidget(send_coef_btn.get());

    coeffs_form_layout->addRow("x = ", hbox_coeffs_layouts[3].get());

    send_x_btn = std::make_unique<QPushButton>("send x", this);
    send_x_btn->setMaximumWidth(75);

    coeffs_form_layout->addWidget(send_x_btn.get());

    val_btn = std::make_unique<QPushButton>("value", this);
    root_btn = std::make_unique<QPushButton>("roots", this);
    classic_btn = std::make_unique<QPushButton>("classic", this);
    cannonic_btn = std::make_unique<QPushButton>("cannonic", this);

    vbox_btns_layout->setSpacing(10);
    vbox_btns_layout->addWidget(val_btn.get());
    vbox_btns_layout->addWidget(root_btn.get());
    vbox_btns_layout->addWidget(classic_btn.get());
    vbox_btns_layout->addWidget(cannonic_btn.get());

    hbox_layout->setSpacing(30);
    hbox_layout->addLayout(coeffs_form_layout.get());
    hbox_layout->addLayout(vbox_btns_layout.get());

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

    connect(integer_radio_btn.get(), SIGNAL(clicked()), this, SLOT(print_inetger_values_form()));
    connect(real_radio_btn.get(), SIGNAL(clicked()), this, SLOT(print_real_values_form()));

    connect(send_x_btn.get(), SIGNAL(pressed()), this, SLOT(send_x_val()));
    connect(send_coef_btn.get(), SIGNAL(pressed()), this, SLOT(send_coeffs()));
    connect(val_btn.get(), SIGNAL(pressed()), this, SLOT(RequestForm()));
    connect(root_btn.get(), SIGNAL(pressed()), this, SLOT(RequestForm()));
    connect(classic_btn.get(), SIGNAL(pressed()), this, SLOT(RequestForm()));
    connect(cannonic_btn.get(), SIGNAL(pressed()), this, SLOT(RequestForm()));
}

void Interface::ClearLayout(QLayout* layout)
{
    if (!layout)
        return;

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        ClearLayout(item->layout());
    }
}

void Interface::print_inetger_values_form()
{
    for (std::size_t i = 0; i < count_coeffs; ++i)
    {
        ClearLayout(hbox_coeffs_layouts[i].get());
        nums[i].release();
        delimetrs[i].release();
        denums[i].release();

        nums[i] = std::make_unique<QLineEdit>("1", this);
        nums[i]->setMaximumWidth(75);
        hbox_coeffs_layouts[i]->addWidget(nums[i].get());
    }
}

void Interface::print_real_values_form()
{
    for (std::size_t i = 0; i < count_coeffs; ++i)
    {
        ClearLayout(hbox_coeffs_layouts[i].get());
        nums[i].release();

        nums[i] = std::make_unique<QLineEdit>("1", this);
        delimetrs[i] = std::make_unique<QLabel>("/", this);
        denums[i] = std::make_unique<QLineEdit>("1", this);

        hbox_coeffs_layouts[i]->addWidget(nums[i].get(), 0, Qt::AlignLeft);
        hbox_coeffs_layouts[i]->addWidget(delimetrs[i].get(), 0);
        hbox_coeffs_layouts[i]->addWidget(denums[i].get(), 1, Qt::AlignLeft);
    }
}


QJsonObject Interface::rationalToJson(int number_coefficint) const
{
    return QJsonObject{
        {"num", nums[number_coefficint]->text().toInt()},
        {"denum", denums[number_coefficint]->text().toInt()}
    };
}


void Interface::send_x_val()
{
    bool real_check = real_radio_btn->isChecked();
    if (nums[3]->isReadOnly())
    {
        nums[3]->setReadOnly(false);
        if (real_check)
            denums[3]->setReadOnly(false);
    }
    else
    {
        nums[3]->setReadOnly(true);
        if (real_check)
            denums[3]->setReadOnly(true);
    }
}


void Interface::send_coeffs()
{
    bool real_check = real_radio_btn->isChecked();
    if (nums[0]->isReadOnly())
    {
        for (std::size_t i = 0; i < nums.size(); ++i)
        {
            nums[i]->setReadOnly(false);
            if (real_check)
                denums[i]->setReadOnly(false);
        }
    }
    else
    {
        for (std::size_t i = 0; i < nums.size(); ++i)
        {
            nums[i]->setReadOnly(true);
            if (real_check)
                denums[i]->setReadOnly(true);
        }
    }
}


void Interface::RequestForm()
{
    bool real_check = real_radio_btn->isChecked();

    QJsonObject json_request;
    QJsonObject json_coeffs;

    if (real_check)
    {
        json_request.insert("number_type", "real");
        json_coeffs.insert("a", rationalToJson(0));
        json_coeffs.insert("b", rationalToJson(1));
        json_coeffs.insert("c", rationalToJson(2));
    }
    else
    {
        json_request.insert("number_type", "int");
        json_coeffs.insert("a", nums[0]->text().toInt());
        json_coeffs.insert("b", nums[1]->text().toInt());
        json_coeffs.insert("c", nums[2]->text().toInt());
    }

    QPushButton* btn_ptr = reinterpret_cast<QPushButton*>(sender());
    if (btn_ptr == val_btn.get())
    {
        if (real_check)
            json_coeffs.insert("x", rationalToJson(3));
        else
            json_coeffs.insert("x", nums[3]->text().toInt());

        json_request.insert("print_type", "value");
        json_request.insert("coeffs", json_coeffs);
    }
    else if (btn_ptr == root_btn.get())
    {
        json_request.insert("print_type", "roots");
        json_request.insert("coeffs", json_coeffs);
    }
    else if (btn_ptr == classic_btn.get())
    {
        json_request.insert("print_type", "classic");
        json_request.insert("coeffs", json_coeffs);
    }
    else if (btn_ptr == cannonic_btn.get())
    {
        json_request.insert("print_type", "canonic");
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
