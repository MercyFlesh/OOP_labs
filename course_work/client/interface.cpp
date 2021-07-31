#include "interface.hpp"

Interface::Interface(QWidget* parent)
    : QTabWidget(parent),
      control_window_ptr(new ControlWindow),
      state_window_ptr(new StateWindow),
      params_window_ptr(new ParamsWindow)
{
    setWindowTitle("Course work");
    setMinimumSize(500, 500);

    addTab(state_window_ptr.get(), "State");
    addTab(params_window_ptr.get(), "Params");
    addTab(control_window_ptr.get(), "Control");

    connect(control_window_ptr.get(), SIGNAL(send_control_req(QJsonObject)), this, SLOT(transfer_inf(QJsonObject)));
    connect(state_window_ptr.get(), SIGNAL(send_state_req(QJsonObject)), this, SLOT(transfer_inf(QJsonObject)));
    connect(params_window_ptr.get(), SIGNAL(send_params_req(QJsonObject)), this, SLOT(transfer_inf(QJsonObject)));
}


void Interface::transfer_inf(QJsonObject data)
{
    emit send_data(data);
}


void Interface::update_tabs(QJsonObject response)
{
    if (response["tab_type"].toString() == "state")
    {
        state_window_ptr->update_state(response);
    }
    else if (response["tab_type"].toString() == "params")
    {
        params_window_ptr->update_params(response);
    }
    else if (response["tab_type"].toString() == "control")
    {
        control_window_ptr->update_control(response);
    }
}
