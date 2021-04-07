#include "app.hpp"
#include "rational.hpp"
#include "polinom.hpp"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <sstream>


App::App(int argc, char *argv[])
    : QCoreApplication(argc, argv),
      com_ptr(new Communicator(QHostAddress::LocalHost, 5000))
{
    connect(com_ptr.get(), SIGNAL(rec(QByteArray msg)),
                      this, SLOT(rec(QByteArray msg)));
}


number App::toRational(QJsonObject coeff)
{
    return number(coeff["num"].toInt(),
                  coeff["denum"].toInt());
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
    QJsonObject coeffs = jsonObj["coeefs"].toObject();

    QJsonObject jsonAns;

    number a(toRational(coeffs["a"].toObject()));
    number b(toRational(coeffs["b"].toObject()));
    number c(toRational(coeffs["c"].toObject()));

    if (jsonObj["type"].toString() == "value")
    {
        number x(toRational(coeffs["x"].toObject()));
        number result = Polinom(a, b, c).calculate_polinom(x);
        QJsonObject val{
            {"num", result.get_numer()},
            {"denum", result.get_denumer()}
        };

        jsonAns.insert("type", "value");
        jsonAns.insert("val", val);
    }
    else if (jsonObj["type"].toString() == "roots")
    {
        jsonAns.insert("type", "roots");

        QJsonObject root_1, root_2;
        if (auto opt_roots = Polinom(a, b, c).get_roots();
                opt_roots.has_value())
        {
            auto [opt_root_1, opt_root_2] = *opt_roots;

            if (opt_root_1.has_value())
            {
                root_1.insert("num", opt_root_1->get_numer());
                root_1.insert("denum", opt_root_1->get_denumer());
            }

            if (opt_root_2.has_value())
            {
                root_2.insert("num", opt_root_2->get_numer());
                root_2.insert("denum", opt_root_2->get_denumer());
            }
        }

        jsonAns.insert("root_1", root_1);
        jsonAns.insert("root_2", root_2);
    }
    else if (jsonObj["type"].toString() == "classic")
    {
        QString str_polynom;
        QTextStream ts(&str_polynom);
        ts << Polinom(a, b, c);

        jsonAns.insert("type", "classic");
        jsonAns.insert("polynom", str_polynom);
    }
    else if (jsonObj["type"].toString() == "canonic")
    {
        Polinom p(a, b, c);
        p.set_print_mode(PrintMode::CANONIC);

        QString str_polynom;
        QTextStream ts(&str_polynom);
        ts << p;

        jsonAns.insert("type", "canonic");
        jsonAns.insert("polynom", str_polynom);
    }

    QJsonDocument jsonDoc_ans;
    jsonDoc_ans.setObject(jsonObj);
    QByteArray dataArray = jsonDoc_ans.toJson();

    com_ptr->send_msg(dataArray);
}
