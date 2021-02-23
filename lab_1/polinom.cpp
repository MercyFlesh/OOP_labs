#include "polinom.hpp"

using namespace std;

Polinom::Polinom(number a, number b, number c)
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


tuple<number, number> Polinom::get_roots() const
{
    number d = pow(b_, 2) - (4 * a_ * c_);
    
    if (d >= 0 )
    {
        number root_1 = (-b_ + sqrt(d)) / (2 * a_);
        number root_2 = (-b_ - sqrt(d)) / (2 * a_);
        if (-a_ * (root_1 + root_2) == b_ &&
            a_ * root_1 * root_2 == c_)
            return { root_1, root_2 };
    }
    
    throw runtime_error("incorect coefficients");
}


ostream& operator<< (ostream& os, const Polinom& p)
{
    if (p.p_mode == PrintMode::CANONIC)
    {
        try
        {
            auto [root_1, root_2] = p.get_roots();
            if (p.a_ != 1)
                os << p.a_ << "*";
            os << showpos << "(x" << -root_1 << ")*(x" << -root_2 << ")" << noshowpos;
        }
        catch (const runtime_error& er)
        {
            os << "[-] this polynom cannot be represented on the set of integers in the canonical form";
        }

        return os;
    }

    return os << p.a_ << "x^2" << showpos << p.b_ << "x" << p.c_ << noshowpos;
}
