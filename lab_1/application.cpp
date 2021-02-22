#include "application.hpp"
#include "console_funcs.hpp"

using namespace std;


int Application::menu() const
{
    cout << "1: coefficients\n";
    cout << "2: roots\n";
    cout << "3: value\n";
    cout << "4: print (classic)\n";
    cout << "5: print (canonical)\n";
    cout << "0 - exit\n" << "> ";
    
    int ch;
    cin >> ch;

    return ch;
}


void Application::send_coefficients()
{
    cout << "a= ";
    cin >> a;
    cout << "b= ";
    cin >> b;
    cout << "c= ";
    cin >> c;
}


void Application::print_roots() const
{   
    try
    {
        auto [root_1, root_2] = Polinom(a, b, c).get_roots();
        if (root_1 == root_2)
            cout << "x = " << root_1 << endl;
        cout << "x_1 = " << root_1 << ", x_2 = " << root_2 << endl;
    }
    catch (const runtime_error& er)
    {
        cerr << "[-] " << er.what() << " : " << a << ", " << b << ", " << c << endl;
    }
}


void Application::print_value() const
{
    number x;
    cin >> x;
    cout << "p(" << x << ") = " << 
        Polinom(a, b, c).calculate_polinom(x) << endl;
}


int Application::exec()
{
    int ch;
    while (true)
    {
        ch = menu();
        switch (ch)
        {
            case 0:
                return 0;
            case 1:
                send_coefficients();
                break;
            case 2:
                print_roots();
                break;
            case 3: 
                print_value();
                break;
            case 4:
                cout << Polinom(a, b, c) << endl;
                break;
            case 5:
            {
                Polinom p(a, b, c);
                p.set_print_mode(Canonic);
                cout << p << endl;
            }    
                break;
            default:
                break;
        }

        cls::pause_output_console();
        cls::clear_console();
    }
}
