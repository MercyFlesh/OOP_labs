#include "model.hpp"
#include <QDebug>

Model::Model()
{

}


bool operator< (const std::shared_ptr<Manager>& lhs_manager,
                 const std::shared_ptr<Manager>& rhs_manager)
{
    return lhs_manager->rating < rhs_manager->rating;
}


void Model::distribute_tasks()
{
    while (waiting_requests.size() != 0 && free_managers.size() != 0)
    {
        std::shared_ptr<Request> request = waiting_requests.front();
        std::shared_ptr<Manager> manager = *free_managers.begin();

        waiting_requests.pop_front();
        free_managers.erase(free_managers.begin());

        request->observing_manager = manager;
        manager->current_task = request;

        busy_managers.push_back(manager);
    }
}


int Model::add_manager(const QString &name, int rating)
{
    int id = managers.size() > 0 ? managers.rbegin()->first + 1 : 0;

    std::shared_ptr<Manager> new_manager =  std::make_shared<Manager>(id, name, rating);
    managers[id] = new_manager;
    free_managers.insert(new_manager);

    distribute_tasks();

    return id;
}


Status Model::delete_manager(int manager_id)
{
    auto managers_it = managers.find(manager_id);
    if (managers_it != managers.end())
    {
        auto free_managers_it = std::find(free_managers.begin(), free_managers.end(), managers_it->second);
        if (free_managers_it != free_managers.end())
        {
            free_managers.erase(free_managers_it);
        }
        else
        {
            auto busy_managers_it = std::find(busy_managers.begin(), busy_managers.end(), managers_it->second);
            if (auto request = (*busy_managers_it)->current_task.lock())
            {
                waiting_requests.push_back(request);
            }

            busy_managers.erase(busy_managers_it);
            distribute_tasks();
        }

        managers.erase(managers_it);

        return Status::SUCCES;
    }

    return Status::FAIL;
}

Status Model::update_manager_rating(int manager_id, int new_rating)
{
    auto managers_it = managers.find(manager_id);
    if (managers_it != managers.end())
    {
        managers[manager_id]->rating = new_rating;

        return Status::SUCCES;
    }

    return Status::FAIL;
}


int Model::add_request(const QString &client_name,
                       const QString &client_email,
                       const QString &description_request)
{
    int id = requests.size() > 0 ? requests.rbegin()->first + 1 : 0;

    std::shared_ptr<Request> new_request = std::make_shared<Request>
            (id, client_name, client_email, description_request);

    requests[id] = new_request;
    waiting_requests.push_back(new_request);

    distribute_tasks();

    return id;
}


Status Model::mark_completed_request(int request_id)
{
    auto request_it = requests.find(request_id);
    if (request_it != requests.end())
    {
        auto manager = (*request_it).second->observing_manager.lock();
        if (manager && manager->current_task.lock() == request_it->second)
        {
            completed_requests.push_back(request_it->second);
            manager->current_task.reset();
            busy_managers.erase(std::remove(busy_managers.begin(), busy_managers.end(), manager));
            free_managers.insert(manager);

            distribute_tasks();
            return Status::SUCCES;
        }
    }

    return Status::FAIL;
}


Status Model::delete_request(int request_id)
{
    auto request_it = requests.find(request_id);
    if (request_it != requests.end())
    {
        auto waiting_requests_it = find_if(waiting_requests.begin(), waiting_requests.end(),
                                           [request_id](auto req_it){ return req_it->id == request_id; });
        auto completed_it = find(completed_requests.begin(), completed_requests.end(), request_it->second);
        if (waiting_requests_it != waiting_requests.end())
        {
            waiting_requests.erase(waiting_requests_it);
        }
        else if (completed_it != completed_requests.end())
        {
            completed_requests.erase(completed_it);
        }
        else if (auto manager = (*request_it).second->observing_manager.lock())
        {
            busy_managers.erase(std::remove(busy_managers.begin(), busy_managers.end(), manager));
            free_managers.insert(manager);

            distribute_tasks();
        }

        requests.erase(request_it);

        return Status::SUCCES;
    }

    return Status::FAIL;
}

std::set<std::shared_ptr<Manager>> Model::get_free_managers_list() const
{
    return free_managers;
}


std::vector<std::shared_ptr<Manager>> Model::get_busy_managers_list() const
{
    return busy_managers;
}


std::vector<std::shared_ptr<Manager>> Model::get_all_managers() const
{
    std::vector<std::shared_ptr<Manager>> result;
    for (const auto& item : managers)
        result.push_back(item.second);

    return result;
}


std::deque<std::shared_ptr<Request>> Model::get_requests_queue() const
{
    return waiting_requests;
}


std::vector<std::shared_ptr<Request>> Model::get_completed_requests() const
{
    return completed_requests;
}


std::vector<std::shared_ptr<Request>> Model::get_all_requests() const
{
    std::vector<std::shared_ptr<Request>> result;
    for (const auto& item : requests)
        result.push_back(item.second);

    return result;
}
