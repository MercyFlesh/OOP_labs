#include "statewindow.hpp"


StateWindow::StateWindow(QWidget* parent)
    : QWidget(parent),
      grid_layout(new QGridLayout(this))
{
    free_managers_label = std::make_unique<QLabel>("Free managers", this);
    busy_managers_label = std::make_unique<QLabel>("Busy managers", this);
    queue_list_label = std::make_unique<QLabel>("Queue requests", this);

    free_managers_list = std::make_unique<QListWidget>(this);
    busy_managers_list = std::make_unique<QListWidget>(this);
    queue_requests_list = std::make_unique<QListWidget>(this);

    update_free_btn = std::make_unique<QPushButton>("update", this);
    update_busy_btn = std::make_unique<QPushButton>("update", this);
    update_queue_btn = std::make_unique<QPushButton>("update", this);

    grid_layout->setVerticalSpacing(10);
    grid_layout->setHorizontalSpacing(15);

    grid_layout->addWidget(free_managers_label.get(), 0, 0, 1, 1);
    grid_layout->addWidget(free_managers_list.get(), 1, 0, 1, 1);
    grid_layout->addWidget(update_free_btn.get(), 2, 0, 1, 1);
    grid_layout->addWidget(busy_managers_label.get(), 0, 2, 1, 1);
    grid_layout->addWidget(busy_managers_list.get(), 1, 2, 1, 1);
    grid_layout->addWidget(update_busy_btn.get(), 2, 2, 1, 1);
    grid_layout->addWidget(queue_list_label.get(), 3, 0, 1, 1);
    grid_layout->addWidget(queue_requests_list.get(), 4, 0, 1, 1);
    grid_layout->addWidget(update_queue_btn.get(), 5, 0, 1, 1);

    setLayout(grid_layout.get());
}
