#pragma once
#include <iostream>
#include <tuple>
#include "number.hpp"


enum class PrintMode {
    CLASSIC,
    CANONIC
};


class Polinom
{
public:
    Polinom(number a, number b, number c);
    number calculate_polinom(const number& x) const;
    std::tuple<number, number> get_roots() const;
    void set_print_mode(const PrintMode& mode);
    
    friend std::ostream& operator<< (std::ostream& os, const Polinom& p);

private:
    const number a_, b_, c_;
    PrintMode p_mode = PrintMode::CLASSIC;
};
