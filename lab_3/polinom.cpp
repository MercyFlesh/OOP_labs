#include "polinom.hpp"
#include <cmath>

using namespace std;


Polinom::Polinom(const number& a, const number& b, const number& c)
    : a_(a), b_(b), c_(c)
{
}


number Polinom::calculate_polinom(const number& x) const
{
    return (a_ * pow(x, 2)) + (b_ * x) + c_;
}


void Polinom::set_print_mode(const PrintMode& mode)
{
    p_mode = mode;
}


optional<array<optional<number>, 2>> Polinom::get_roots() const
{
    number d = pow(b_, 2) - (static_cast<number>(4) * a_ * c_);


    if (d >= 0)
    {
        number root_1 = (-b_ + sqrt(d)) / (static_cast<number>(2) * a_);
        number root_2 = (-b_ - sqrt(d)) / (static_cast<number>(2) * a_);
        bool check_root_1 = calculate_polinom(root_1) == 0;
        bool check_root_2 = calculate_polinom(root_2) == 0;

        if (check_root_1 || check_root_2)
        {
            array<optional<number>, 2> roots;
            if (check_root_1)
                roots[0] = root_1;

            if (check_root_2)
                roots[1] = root_2;

            return roots;
        }
    }

    return nullopt;
}


ostream& operator<< (ostream& os, const Polinom& p)
{
    if (p.p_mode == PrintMode::CANONIC)
    {
        if (auto opt_roots = p.get_roots(); opt_roots.has_value())
        {
            auto [opt_root_1, opt_root_2] = *opt_roots;
            if (opt_root_1.has_value() && opt_root_2.has_value())
            {
                if (p.a_ != 1)
                    os << p.a_ << "*";
                return os << "(x" << showpos << -(*opt_root_1) << ")*(x" << showpos << -(*opt_root_2) << ")" << noshowpos;
            }
        }

        return os << "[-] this polynom cannot be represented on the set of integers in the canonical form";;
    }

    if (p.a_ != 1)
        os << p.a_;
    return os << "x^2" << showpos << p.b_ << "x" << showpos << p.c_ << noshowpos;
}


