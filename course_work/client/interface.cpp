#include "interface.hpp"

Interface::Interface(QWidget* parent)
    : QTabWidget(parent),
      control_window_ptr(new ControlWindow),
      state_window_ptr(new StateWindow),
      params_window_ptr(new ParamsWindow)
{
    setWindowTitle("Course work");

    addTab(state_window_ptr.get(), "State");
    addTab(params_window_ptr.get(), "Params");
    addTab(control_window_ptr.get(), "Control");

    //connect(tab_widgets_ptr.get(), SIGNAL(currentChanged()), this, SLOT(showTabPageIndex()));
}
