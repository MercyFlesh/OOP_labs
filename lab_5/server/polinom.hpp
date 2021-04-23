#pragma once
#include <iostream>
#include <array>
#include <optional>
#include <cmath>
#include <QTextStream>
#include <QString>


enum class PrintMode {
    CLASSIC,
    CANONIC
};


template<typename number>
class Polinom
{
public:
    Polinom(number a, number b, number c);

    number calculate_polinom(const number& x) const;
    std::optional<std::array<std::optional<number>, 2>> get_roots() const;
    void set_print_mode(const PrintMode& mode);

    template<typename T>
    friend std::ostream& operator<< (std::ostream& os, const Polinom<T>& p);
    template<typename T>
    friend QTextStream& operator<< (QTextStream& ts, const Polinom<T>& p);

private:
    number a_, b_, c_;
    PrintMode p_mode = PrintMode::CLASSIC;
};


template<typename number>
Polinom<number>::Polinom(number a, number b, number c)
    : a_(a), b_(b), c_(c)
{
}


template<typename number>
number Polinom<number>::calculate_polinom(const number& x) const
{
    return (a_ * pow(x, 2)) + (b_ * x) + c_;
}


template<typename T>
void Polinom<T>::set_print_mode(const PrintMode& mode)
{
    p_mode = mode;
}


template<typename number>
std::optional<std::array<std::optional<number>, 2>> Polinom<number>::get_roots() const
{
    number d = pow(b_, 2) - (static_cast<number>(4) * a_ * c_);


    if (d >= static_cast<number>(0))
    {
        number root_1 = (-b_ + sqrt(d)) / (static_cast<number>(2) * a_);
        number root_2 = (-b_ - sqrt(d)) / (static_cast<number>(2) * a_);
        bool check_root_1 = calculate_polinom(root_1) == static_cast<number>(0);
        bool check_root_2 = calculate_polinom(root_2) == static_cast<number>(0);

        if (check_root_1 || check_root_2)
        {
            std::array<std::optional<number>, 2> roots;
            if (check_root_1)
                roots[0] = root_1;

            if (check_root_2)
                roots[1] = root_2;

            return roots;
        }
    }

    return std::nullopt;
}


template<typename T>
std::ostream& operator<< (std::ostream& os, const Polinom<T>& p)
{
    if (p.p_mode == PrintMode::CANONIC)
    {
        if (auto opt_roots = p.get_roots(); opt_roots.has_value())
        {
            auto [opt_root_1, opt_root_2] = *opt_roots;
            if (opt_root_1.has_value() && opt_root_2.has_value())
            {
                if (p.a_ != static_cast<T>(1))
                    os << p.a_ << "*";
                return os << "(x" << std::showpos << -(*opt_root_1) << ")*(x" <<
                             std::showpos << -(*opt_root_2) << ")" << std::noshowpos;
            }
        }

        return os << "[-] this polynom cannot be represented on this set in the canonical form";
    }

    if (p.a_ != static_cast<T>(1))
        os << p.a_;
    return os << "x^2" << std::showpos << p.b_ << "x" <<
                 std::showpos << p.c_ << std::noshowpos;
}


template<typename T>
QTextStream& operator<< (QTextStream& ts, const Polinom<T>& p)
{
    if (p.p_mode == PrintMode::CANONIC)
    {
        if (auto opt_roots = p.get_roots(); opt_roots.has_value())
        {
            auto [opt_root_1, opt_root_2] = *opt_roots;
            if (opt_root_1.has_value() && opt_root_2.has_value())
            {
                if (p.a_ != static_cast<T>(1))
                    ts << p.a_ << "*";

                return ts << "(x" << Qt::forcesign << -(*opt_root_1) << ")*(x" <<
                             Qt::forcesign << -(*opt_root_2) << ")" << Qt::noforcesign;
            }
        }

        return ts << "[-] this polynom cannot be represented on this set in the canonical form";
    }

    if (p.a_ != static_cast<T>(1))
        ts << p.a_;
    return ts << "x^2" << Qt::forcesign << p.b_ << "x" << Qt::forcesign << p.c_ << Qt::noforcesign;
}
