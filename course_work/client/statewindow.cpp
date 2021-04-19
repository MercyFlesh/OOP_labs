#include "statewindow.hpp"

StateWindow::StateWindow(QWidget* parent)
    : QWidget(parent),
      vbox_main_layout(new QVBoxLayout(this))
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

    vbox_free = std::make_unique<QVBoxLayout>(this);
    vbox_busy = std::make_unique<QVBoxLayout>(this);
    hbox_managers_lists = std::make_unique<QHBoxLayout>(this);
    vbox_free->setSpacing(15);
    vbox_busy->setSpacing(15);
    hbox_managers_lists->setSpacing(15);

    vbox_free->addWidget(free_managers_label.get());
    vbox_free->addWidget(free_managers_list.get());
    vbox_free->addWidget(update_free_btn.get());
    vbox_busy->addWidget(busy_managers_label.get());
    vbox_busy->addWidget(busy_managers_list.get());
    vbox_busy->addWidget(update_busy_btn.get());

    hbox_managers_lists->addLayout(vbox_free.get());
    hbox_managers_lists->addLayout(vbox_busy.get());

    vbox_queue_list->addWidget(queue_list_label.get());
    vbox_queue_list->addWidget(queue_requests_list.get());
    vbox_queue_list->addWidget(update_queue_btn.get());

    vbox_main_layout->setSpacing(15);
    vbox_main_layout->addLayout(hbox_managers_lists.get());
    vbox_main_layout->addLayout(vbox_queue_list.get());

    setLayout(vbox_main_layout.get());
}
