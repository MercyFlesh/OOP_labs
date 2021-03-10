#pragma once
#include <iostream>
#include <tuple>
#include "number.hpp"
#include "polinom.hpp"

class Application
{
    int menu() const;
    void send_coefficients();
    void print_roots() const;
    void print_value() const;

public:
    int exec();

private:
    number a = 1, b = 3, c = 2;
};
