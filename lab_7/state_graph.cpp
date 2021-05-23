#include "state_graph.hpp"


StateGraph::StateGraph(Matrix transition_matrix, Matrix event_matrix)
    : Graph(transition_matrix), event_matrix_(event_matrix), active_vertex(0)
{
}


void StateGraph::set_graph_window(std::weak_ptr<GraphWindow> graphWindow)
{
    graphWindow_ = std::move(graphWindow);
}


void StateGraph::set_active_vertex(int num_vertex)
{
    active_vertex = num_vertex;
}


int StateGraph::get_active_vertex() const
{
    return active_vertex;
}


QVector<qint16> StateGraph::get_events_vertex(int number_vertex) const
{
    return event_matrix_.at(number_vertex);
}


