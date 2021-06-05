#include "app.hpp"

App::App(int argc, char* argv[])
    : QCoreApplication(argc, argv),
      server(new Server(QHostAddress::LocalHost, 5000)),
      model(new Model())
{
    connect(server.get(), SIGNAL(rec(int,QByteArray)),
                     this, SLOT(rec(int,QByteArray)));
}


void App::make_response(int client_index, QJsonObject jsonObj)
{
    QJsonDocument jsonDoc_ans;
    jsonDoc_ans.setObject(jsonObj);
    QByteArray dataArray = jsonDoc_ans.toJson();

    server->send(client_index, dataArray);
}


void App::rec(int client_index, QByteArray request)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc_req = QJsonDocument::fromJson(request, &json_error);
    if (json_error.error!= QJsonParseError::NoError)
    {
        qDebug() << "json error";
        return;
    }

    QJsonObject jsonObj = jsonDoc_req.object();

    if (jsonObj["type"].toString() == "control")
    {
        if (jsonObj["action"].toString() == "add_request")
        {
            int id = model->add_request(jsonObj["name"].toString(),
                    jsonObj["email"].toString(),
                    jsonObj["description"].toString());


            make_response(client_index, QJsonObject{
                              {"tab_type", "control"},
                              {"action", "new_request"},
                              {"id", id}}
                          );
        }
        else if (jsonObj["action"].toString() == "del_request")
        {
            if (model->delete_request(jsonObj["id_request"].toInt()) == Status::SUCCES)
                make_response(client_index,QJsonObject{
                                  {"tab_type", "control"},
                                  {"action", "del_succes"}});
            else
                make_response(client_index,QJsonObject{
                                  {"tab_type", "control"},
                                  {"action", "del_fail"}});
        }
        else if (jsonObj["action"].toString() == "complete_request")
        {
            if (model->mark_completed_request(jsonObj["id_request"].toInt()) == Status::SUCCES)
                make_response(client_index,QJsonObject{
                                  {"tab_type", "control"},
                                  {"action", "complete_succes"}});
            else
                make_response(client_index,QJsonObject{
                                  {"tab_type", "control"},
                                  {"action", "complete_fail"}});
        }
    }
    else if (jsonObj["type"] == "params")
    {
        if (jsonObj["action"].toString() == "add_manager")
        {
            int id = model->add_manager(jsonObj["name"].toString(), jsonObj["rating"].toInt());
            make_response(client_index, QJsonObject{
                              {"tab_type", "params"},
                              {"action", "new_manager"},
                              {"id", id}});
        }
        else if (jsonObj["action"].toString() == "update_rating")
        {
            Status status = model->update_manager_rating(jsonObj["id"].toInt(), jsonObj["rating"].toInt());
            if (status == Status::SUCCES)
                make_response(client_index, QJsonObject{
                                  {"tab_type", "params"},
                                  {"action", "update_succes"}});
            else
                make_response(client_index, QJsonObject{
                                  {"tab_type", "params"},
                                  {"action", "update_fail"}});
        }
        else if (jsonObj["action"].toString() == "delete_manager")
        {
            Status status = model->delete_manager(jsonObj["id"].toInt());
            if (status == Status::SUCCES)
                make_response(client_index, QJsonObject{
                                  {"tab_type", "params"},
                                  {"action", "delete_succes"}});
            else
                make_response(client_index, QJsonObject{
                                  {"tab_type", "params"},
                                  {"action", "delete_fail"}});
        }

    }
    else if (jsonObj["type"] == "state")
    {
        QJsonObject response{{"tab_type", "state"}};
        if (jsonObj["action"].toString() == "free_managers")
        {
            QJsonArray managers_array;
            for (const auto& manager : model->get_free_managers_list())
            {
                managers_array.append(QJsonObject{
                                  {"id", manager->id},
                                  {"name", manager->name},
                                  {"rating", manager->rating}
                              });
            }

            response.insert("action", "free_managers");
            response.insert("response_list", managers_array);
        }
        else if (jsonObj["action"].toString() == "busy_managers")
        {
            QJsonArray managers_array;
            for (const auto& manager : model->get_busy_managers_list())
            {
                managers_array.append(QJsonObject{
                                  {"id", manager->id},
                                  {"name", manager->name},
                                  {"task_id", manager->current_task.lock()->id}
                              });
            }

            response.insert("action", "busy_managers");
            response.insert("response_list", managers_array);
        }
        else if (jsonObj["action"].toString() == "all_managers")
        {
            QJsonArray managers_array;
            for (const auto& manager : model->get_all_managers())
            {
                managers_array.append(QJsonObject{
                                  {"id", manager->id},
                                  {"name", manager->name},
                                  {"rating", manager->rating}
                              });
            }

            response.insert("action", "all_managers");
            response.insert("response_list", managers_array);
        }
        else if (jsonObj["action"].toString() == "queue_requests")
        {
            QJsonArray requests_array;
            for (const auto& request : model->get_requests_queue())
            {
                requests_array.append(QJsonObject{
                                  {"id", request->id},
                                  {"name", request->client_name},
                                  {"email", request->client_email}
                              });
            }

            response.insert("action", "queue_requests");
            response.insert("response_list", requests_array);
        }
        else if (jsonObj["action"].toString() == "completed_requests")
        {
            QJsonArray requests_array;
            for (const auto& request : model->get_completed_requests())
            {
                QJsonObject json_res{{"id", request->id},
                            {"name", request->client_name},
                            {"email", request->client_email}};

                if (auto manager = request->observing_manager.lock())
                    json_res.insert("manager_id", manager->id);

                requests_array.append(json_res);
            }

            response.insert("action", "completed_requests");
            response.insert("response_list", requests_array);
        }
        else if (jsonObj["action"].toString() == "all_requests")
        {
            QJsonArray requests_array;
            for (const auto& request : model->get_all_requests())
            {
                requests_array.append(QJsonObject{
                                  {"id", request->id},
                                  {"name", request->client_name},
                                  {"email", request->client_email}
                              });
            }

            response.insert("action", "all_requests");
            response.insert("response_list", requests_array);
        }

        make_response(client_index, response);
    }
}
