#include "interface.hpp"

Interface::Interface(QWidget* parent)
    : QMainWindow(parent), tab_widgets_ptr(new QTabWidget(this)),
      control_window_ptr(new ControlWindow), state_window_ptr(new StateWindow),
      params_window_ptr(new ParamsWindow)
{
    setWindowTitle("Course work");
    setBaseSize(400, 30);

    tab_widgets_ptr->setFixedSize(3840, 2160);
    tab_widgets_ptr->addTab(state_window_ptr.get(), "State");
    tab_widgets_ptr->addTab(params_window_ptr.get(), "Params");
    tab_widgets_ptr->addTab(control_window_ptr.get(), "Control");

    //connect(tab_widgets_ptr.get(), SIGNAL(currentChanged()), this, SLOT(showTabPageIndex()));
}
