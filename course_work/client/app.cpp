#include "app.hpp"

App::App(int argc, char* argv[])
    : QApplication(argc, argv),
      interface_ptr(new Interface),
      client_ptr(new Client(QHostAddress::LocalHost, 5000))
{
    interface_ptr->show();
}
