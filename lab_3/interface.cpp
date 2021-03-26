#include "interface.hpp"
#include "polinom.hpp"

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
    connect(val_btn.get(), SIGNAL(pressed()), this, SLOT(print_value()));
    connect(root_btn.get(), SIGNAL(pressed()), this, SLOT(print_roots()));
    connect(classic_btn.get(), SIGNAL(pressed()), this, SLOT(print_classic()));
    connect(cannonic_btn.get(), SIGNAL(pressed()), this, SLOT(print_cannonic()));
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

        x = number(x_num->text().toInt(), x_denum->text().toInt());
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

            coeffs[i] = number(
                            nums[i]->text().toInt(),
                            denums[i]->text().toInt());
        }
    }
}


void Interface::print_value() const
{
    number val = Polinom(
                coeffs[0], coeffs[1], coeffs[2]).calculate_polinom(x);

    /*std::stringstream ts;
    ts << val;
    QString str(QString::fromStdString(ts.str()));*/
    QString str;
    QTextStream ts(&str);
    ts << val;
    output->setText(str);
}


void Interface::print_roots() const
{
    QString str;
    QTextStream ts(&str);
    if (auto opt_roots = Polinom(coeffs[0], coeffs[1], coeffs[2]).get_roots();
            opt_roots.has_value())
    {
        auto [opt_root_1, opt_root_2] = *opt_roots;

        if (opt_root_1.has_value())
            ts << "x_1=" << *opt_root_1 << "\t";

        if (opt_root_2.has_value())
            ts << "x_2=" << *opt_root_2;
     }
     else
         ts << "[-] no roots in the given field with this coefficints";

     output->setText(str);
}


void Interface::print_classic() const
{
    QString str;
    QTextStream ts(&str);
    ts << Polinom(coeffs[0], coeffs[1], coeffs[2]);

    output->setText(str);
}


void Interface::print_cannonic() const
{
    Polinom p(coeffs[0], coeffs[1], coeffs[2]);
    p.set_print_mode(PrintMode::CANONIC);

    QString str;
    QTextStream ts(&str);
    ts << p;

    output->setText(str);
}
