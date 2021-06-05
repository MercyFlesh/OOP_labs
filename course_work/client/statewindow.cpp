#include "statewindow.hpp"


StateWindow::StateWindow(QWidget* parent)
    : QWidget(parent),
      main_layout(new QVBoxLayout(this))
{
    states_table = std::make_unique<QTableWidget>(this);

    update_btn = std::make_unique<QPushButton>("update", this);
    states_box = std::make_unique<QComboBox>(this);
    states_box->addItem("Free managers", "free_managers");
    states_box->addItem("Busy managers", "busy_managers");
    states_box->addItem("All managers", "all_managers");
    states_box->addItem("All requests", "all_requests");
    states_box->addItem("Queue waiting requests", "queue_requests");
    states_box->addItem("Completed requests", "completed_requests");

    hbox_choice_layout = std::make_unique<QHBoxLayout>();
    hbox_choice_layout->addWidget(states_box.get(), 1);
    hbox_choice_layout->addWidget(update_btn.get(), 0, Qt::AlignRight);
    hbox_choice_layout->setSpacing(15);
    main_layout->setSpacing(10);

    main_layout->addLayout(hbox_choice_layout.get());
    main_layout->addWidget(states_table.get());
    setLayout(main_layout.get());

    connect(update_btn.get(), SIGNAL(pressed()), this, SLOT(send_request()));
}


void StateWindow::send_request()
{
    QString action_name = states_box->currentData().toString();

    QJsonObject state_request;
    state_request.insert("type", "state");
    state_request.insert("action", action_name);

    emit send_state_req(state_request);
}


void StateWindow::update_state(QJsonObject response)
{
    states_table->clear();
    QJsonArray json_list = response["response_list"].toArray();
    QStringList header;

    if (response["action"].toString() == "free_managers" ||
        response["action"].toString() == "all_managers")
    {
        states_table->setRowCount(json_list.size() + 1);
        states_table->setColumnCount(3);
        header << "id" << "name" << "rating";
        states_table->setHorizontalHeaderLabels(header);

        for (std::size_t i = 1; i < json_list.size() + 1; ++i)
        {
            QJsonObject json_manager = json_list[i-1].toObject();
            QTableWidgetItem* item_id = new QTableWidgetItem(QString().number(json_manager["id"].toInt()));
            QTableWidgetItem* item_name = new QTableWidgetItem(json_manager["name"].toString());
            QTableWidgetItem* item_rating = new QTableWidgetItem(QString().number(json_manager["rating"].toInt()));

            states_table->setItem(i, 0, item_id);
            states_table->setItem(i, 1, item_name);
            states_table->setItem(i, 2, item_rating);
        }
    }
    else if (response["action"].toString() == "busy_managers")
    {
        states_table->setRowCount(json_list.size() + 1);
        states_table->setColumnCount(3);
        header << "id" << "name" << "task id";
        states_table->setHorizontalHeaderLabels(header);

        for (std::size_t i = 1; i < json_list.size() + 1; ++i)
        {
            QJsonObject json_manager = json_list[i-1].toObject();
            QTableWidgetItem* item_id = new QTableWidgetItem(QString().number(json_manager["id"].toInt()));
            QTableWidgetItem* item_name = new QTableWidgetItem(json_manager["name"].toString());
            QTableWidgetItem* item_rating = new QTableWidgetItem(QString().number(json_manager["task_id"].toInt()));

            states_table->setItem(i, 0, item_id);
            states_table->setItem(i, 1, item_name);
            states_table->setItem(i, 2, item_rating);
        }
    }
    else if (response["action"].toString() == "queue_requests" ||
             response["action"].toString() == "all_requests")
    {
        states_table->setRowCount(json_list.size() + 1);
        states_table->setColumnCount(3);
        header << "id" << "Client name" << "Client email";
        states_table->setHorizontalHeaderLabels(header);

        for (std::size_t i = 1; i < json_list.size() + 1; ++i)
        {
            QJsonObject json_manager = json_list[i-1].toObject();
            QTableWidgetItem* item_id = new QTableWidgetItem(QString().number(json_manager["id"].toInt()));
            QTableWidgetItem* item_name = new QTableWidgetItem(json_manager["name"].toString());
            QTableWidgetItem* item_email = new QTableWidgetItem(json_manager["email"].toString());

            states_table->setItem(i, 0, item_id);
            states_table->setItem(i, 1, item_name);
            states_table->setItem(i, 2, item_email);
        }
    }
    else if (response["action"].toString() == "completed_requests")
    {
        states_table->setRowCount(json_list.size() + 1);
        states_table->setColumnCount(4);
        header << "id" << "Client name" << "Client email" << "Manager id";
        states_table->setHorizontalHeaderLabels(header);

        for (std::size_t i = 1; i < json_list.size() + 1; ++i)
        {
            QJsonObject json_manager = json_list[i-1].toObject();
            QTableWidgetItem* item_id = new QTableWidgetItem(QString().number(json_manager["id"].toInt()));
            QTableWidgetItem* item_name = new QTableWidgetItem(json_manager["name"].toString());
            QTableWidgetItem* item_email = new QTableWidgetItem(json_manager["email"].toString());
            QTableWidgetItem* item_manager = new QTableWidgetItem(QString().number(json_manager.value("manager_id").toInt()));

            states_table->setItem(i, 0, item_id);
            states_table->setItem(i, 1, item_name);
            states_table->setItem(i, 2, item_email);
            states_table->setItem(i, 3, item_manager);
        }
    }
}
