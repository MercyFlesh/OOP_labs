#pragma once

#include <QObject>

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <deque>
#include <set>
#include <tuple>

struct Manager;
struct Request;


struct Manager {
    int id;
    QString name;
    int rating;
    std::weak_ptr<Request> current_task;

    Manager() = default;
    ~Manager() = default;
    Manager(int id_, const QString& name_, int rating_)
        : id(id_), name(name_), rating(rating_)
    {
    }
};


struct Request {
    int id;
    QString client_name;
    QString client_email;
    QString description_request;
    std::weak_ptr<Manager> observing_manager;

    Request() = default;
    ~Request() = default;
    Request(int id_, const QString& name, const QString& email, const QString description)
        : id(id_), client_name(name), client_email(email), description_request(description)
    {
    }
};


enum class Status {
    SUCCES,
    FAIL
};


class Model
{
public:
    Model();

    int add_request(const QString& client_name,
                    const QString& client_email,
                    const QString& description_request);
    Status mark_completed_request(int request_id);
    Status delete_request(int request_id);

    int add_manager(const QString& name, int rating);
    Status update_manager_rating(int manager_id, int raing);
    Status delete_manager(int manager_id);

    std::set<std::shared_ptr<Manager>> get_free_managers_list() const;
    std::vector<std::shared_ptr<Manager>> get_busy_managers_list() const;
    std::vector<std::shared_ptr<Manager>> get_all_managers() const;

    std::deque<std::shared_ptr<Request>> get_requests_queue() const;
    std::vector<std::shared_ptr<Request>> get_completed_requests() const;
    std::vector<std::shared_ptr<Request>> get_all_requests() const;

private:
    void distribute_tasks();

private:
    std::deque<std::shared_ptr<Request>> waiting_requests;
    std::vector<std::shared_ptr<Request>> completed_requests;
    std::map<int, std::shared_ptr<Request>> requests;

    std::vector<int> managers_id;
    std::set<std::shared_ptr<Manager>> free_managers;
    std::vector<std::shared_ptr<Manager>> busy_managers;
    std::map<int, std::shared_ptr<Manager>> managers;
};
