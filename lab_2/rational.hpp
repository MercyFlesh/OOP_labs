#pragma once
#include <iostream>
#include <cmath>

class Rational
{
public:
	Rational() = default;
	Rational(int a);
	Rational(int a, int b);

	void reduct();
	
	Rational operator- () const;
	Rational operator+ (const Rational& rhs) const;
	Rational operator- (const Rational& rhs) const;
	Rational operator* (const Rational& rhs) const;
	Rational operator/ (const Rational& rhs) const;
	
	Rational& operator*= (const Rational& rhs);
	Rational& operator/= (const Rational& rhs);
	
	bool operator== (const Rational& rhs) const;
	bool operator!= (const Rational& rhs) const;
	bool operator< (const Rational& rhs) const;
	bool operator>= (const Rational& rhs) const;
	
	friend Rational sqrt(const Rational& rt);
	friend Rational pow(const Rational& rt, const int& power);
	friend std::ostream& operator<< (std::ostream& os, const Rational& r);
	friend std::istream& operator>> (std::istream& is, Rational& r);

private:
	int a_;
	int b_;
};
