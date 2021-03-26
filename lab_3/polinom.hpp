#pragma once
#include <iostream>
#include <array>
#include <optional>
#include "number.hpp"


enum class PrintMode {
    CLASSIC,
    CANONIC
};

class Polinom
{
public:
    Polinom(const number& a, const number& b, const number& c);

    number calculate_polinom(const number& x) const;
    std::optional<std::array<std::optional<number>, 2>> get_roots() const;
    void set_print_mode(const PrintMode& mode);

    friend std::ostream& operator<< (std::ostream& os, const Polinom& p);

private:
    number a_, b_, c_;
    PrintMode p_mode = PrintMode::CLASSIC;
};
