#pragma once
#include <QTextStream>
#include <iostream>
#include <cmath>


class Rational
{
    void reduct();
    int gcd(int a, int b);

public:
    Rational() = default;
    explicit Rational(int a);
    explicit Rational(int a, int b);
    Rational(const Rational& rt);
    Rational& operator= (const Rational& rhs);

    int get_numer() const;
    int get_denumer() const;

    Rational operator- () const;
    Rational operator+ (const Rational& rhs) const;
    Rational operator- (const Rational& rhs) const;
    Rational operator* (const Rational& rhs) const;
    Rational operator/ (const Rational& rhs) const;

    Rational& operator*= (const Rational& rhs);
    Rational& operator/= (const Rational& rhs);

    //operator double() const;
    bool operator== (const Rational& rhs) const;
    bool operator!= (const Rational& rhs) const;
    bool operator< (const Rational& rhs) const;
    bool operator>= (const Rational& rhs) const;

    friend Rational sqrt(const Rational& rt);
    friend Rational pow(const Rational& base, int exp);
    friend std::ostream& operator<< (std::ostream& os, const Rational& r);
    friend QTextStream& operator<< (QTextStream& qs, const Rational& r);
    friend std::istream& operator>> (std::istream& is, Rational& r);

private:
    int a_;
    int b_;
};
