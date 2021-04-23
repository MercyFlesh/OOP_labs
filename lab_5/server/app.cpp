#include "app.hpp"
#include "polinom.hpp"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <sstream>


App::App(int argc, char *argv[])
    : QCoreApplication(argc, argv),
      com_ptr(new Communicator(QHostAddress::LocalHost, 5000,
                               QHostAddress::LocalHost, 5001))
{
    connect(com_ptr.get(), SIGNAL(rec(QByteArray)),
                      this, SLOT(rec(QByteArray)));
}



Rational App::toRational(QJsonObject coeff)
{
    return Rational(coeff["num"].toInt(),
                  coeff["denum"].toInt());
}


template<typename number>
void App::make_response(QJsonObject jsonObj,
                        number a, number b, number c, std::optional<number> x)
{
    QJsonObject jsonAns;

    if (jsonObj["print_type"].toString() == "value")
    {
        number result = Polinom<number>(a, b, c).calculate_polinom(*x);

        QString str_val;
        QTextStream ts(&str_val);
        ts << result;

        jsonAns.insert("type", "value");
        jsonAns.insert("val", str_val);
    }
    else if (jsonObj["print_type"].toString() == "roots")
    {
        jsonAns.insert("type", "roots");

        QString root_1, root_2;
        if (auto opt_roots = Polinom<number>(a, b, c).get_roots();
                opt_roots.has_value())
        {
            auto [opt_root_1, opt_root_2] = *opt_roots;

            if (opt_root_1.has_value())
            {
                QTextStream ts(&root_1);
                ts << *opt_root_1;
            }

            if (opt_root_2.has_value())
            {
                QTextStream ts(&root_2);
                ts << *opt_root_2;
            }
        }

        jsonAns.insert("root_1", root_1);
        jsonAns.insert("root_2", root_2);
    }
    else if (jsonObj["print_type"].toString() == "classic")
    {
        QString str_polynom;
        QTextStream ts(&str_polynom);
        ts << Polinom<number>(a, b, c);

        jsonAns.insert("type", "classic");
        jsonAns.insert("polynom", str_polynom);
    }
    else if (jsonObj["print_type"].toString() == "canonic")
    {
        Polinom<number> p(a, b, c);
        p.set_print_mode(PrintMode::CANONIC);

        QString str_polynom;
        QTextStream ts(&str_polynom);
        ts << p;

        jsonAns.insert("type", "canonic");
        jsonAns.insert("polynom", str_polynom);
    }

    QJsonDocument jsonDoc_ans;
    jsonDoc_ans.setObject(jsonAns);
    QByteArray dataArray = jsonDoc_ans.toJson();

    com_ptr->send_msg(dataArray);
}


void App::rec(QByteArray requst)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc_req = QJsonDocument::fromJson(requst, &json_error);
    if (json_error.error!= QJsonParseError::NoError)
    {
        qDebug() << "json error";
        return;
    }

    QJsonObject jsonObj = jsonDoc_req.object();
    QJsonObject coeffs = jsonObj["coeffs"].toObject();

    if (jsonObj["number_type"].toString() == "real")
    {
        std::optional<Rational> x;
        Rational a(toRational(coeffs["a"].toObject()));
        Rational b(toRational(coeffs["b"].toObject()));
        Rational c(toRational(coeffs["c"].toObject()));

        if (jsonObj["print_type"] == "value")
            x = toRational(coeffs["x"].toObject());

        make_response<Rational>(jsonObj, a, b, c, x);
    }
    else if (jsonObj["number_type"].toString() == "int")
    {
        std::optional<int> x;
        if (jsonObj["print_type"] == "value")
            x = coeffs["x"].toInt();

        make_response<int>(jsonObj, coeffs["a"].toInt(), coeffs["b"].toInt(), coeffs["c"].toInt(), x);
    }
}
