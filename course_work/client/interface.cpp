#include "interface.hpp"

Interface::Interface(QWidget* parent)
    : QTabWidget(parent),
      control_window_ptr(new ControlWindow),
      state_window_ptr(new StateWindow),
      params_window_ptr(new ParamsWindow)
{
    setWindowTitle("Course work");
    setBaseSize(400, 600);
    setMinimumSize(300, 400);

    addTab(state_window_ptr.get(), "State");
    addTab(params_window_ptr.get(), "Params");
    addTab(control_window_ptr.get(), "Control");
}


void Interface::update_tabs(QJsonObject response)
{
    if (response["tab_type"].toString() == "state")
    {
        state_window_ptr->update_state(response);
    }
    else if (response["tab_type"].toString() == "control")
    {
        control_window_ptr->update_control(response);
    }
}
