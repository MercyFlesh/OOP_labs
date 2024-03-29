#include "rational.hpp"

using namespace std;


Rational::Rational(int a)
    : a_(a), b_(1)
{
}


Rational::Rational(int a, int b)
    : a_(a), b_(b)
{
    reduct();
}


Rational::Rational(const Rational& rt)
{
    a_ = rt.a_;
    b_ = rt.b_;
}


Rational& Rational::operator= (const Rational& rhs)
{
    a_ = rhs.a_;
    b_ = rhs.b_;

    return *this;
}


int Rational::gcd(int a, int b)
{
    if (a % b == 0)
        return abs(b);
    else if (b % a == 0)
        return abs(a);

    return a == 0 ? abs(b) : gcd(b % a, a);
}


void Rational::reduct()
{
    int factor = gcd(a_, b_);
    a_ /= factor;
    b_ /= factor;

    if (b_ < 0)
    {
        a_ *= -1;
        b_ *= -1;
    }
}


int Rational::get_numer() const
{
    return a_;
}


int Rational::get_denumer() const
{
    return b_;
}


Rational& Rational::operator*= (const Rational& rhs)
{
    a_ *= rhs.a_;
    b_ *= rhs.b_;
    reduct();

    return *this;
}


Rational& Rational::operator/= (const Rational& rhs)
{
    a_ *= rhs.b_;
    b_ *= rhs.a_;
    reduct();

    return *this;
}


Rational Rational::operator+ (const Rational& rhs) const
{
    int num = (a_ * rhs.b_) + (rhs.a_ * b_);
    int den = b_ * rhs.b_;
    return Rational(num, den);
}


Rational Rational::operator- (const Rational& rhs) const
{
    int num = (a_ * rhs.b_) - (rhs.a_ * b_);
    int den = b_ * rhs.b_;
    return Rational(num, den);
}


Rational Rational::operator* (const Rational& rhs) const
{
    return Rational(a_ * rhs.a_, b_ * rhs.b_);
}


Rational Rational::operator/ (const Rational& rhs) const
{
    return Rational(a_ * rhs.b_, b_ * rhs.a_);
}


Rational Rational::operator- () const
{
    return Rational(-a_, b_);
}


bool Rational::operator== (const Rational& rhs) const
{
    return a_ == rhs.a_ && b_ == rhs.b_;
}


bool Rational::operator!= (const Rational& rhs) const
{
    return a_ != rhs.a_ || b_ != rhs.b_;
}


bool Rational::operator< (const Rational& rhs) const
{
    return (a_ * rhs.b_) < (rhs.a_ * b_);
}


bool Rational::operator>= (const Rational& rhs) const
{
    return (a_ * rhs.b_) >= (rhs.a_ * b_);
}


Rational sqrt(const Rational& rt)
{
    return Rational(sqrt(rt.a_), sqrt(rt.b_));
}


Rational pow(const Rational& base, int exp)
{
    return Rational(pow(base.a_, exp), pow(base.b_, exp));
}


istream& operator>> (istream& is, Rational& rt)
{
    is >> rt.a_;
    is.ignore();
    is >> rt.b_;
    rt.reduct();

    return is;
}


ostream& operator<< (ostream& os, const Rational& rt)
{
    os << rt.a_;
    if (rt.b_ != 1)
        os << "/" << noshowpos << rt.b_;

    return os;
}

QTextStream& operator<< (QTextStream& qs, const Rational& rt)
{
    qs << rt.a_;
    if (rt.b_ != 1)
         qs << "/" << Qt::noforcesign << rt.b_;

    return qs;
}
