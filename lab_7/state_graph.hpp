#pragma once

#include "graph.hpp"
#include "graphwindow.hpp"

class GraphWindow;


class StateGraph : public Graph
{
public:
    StateGraph(Matrix transition_matrix, Matrix event_matrix);
    void set_graph_window(std::weak_ptr<GraphWindow> graphWindow);
    void set_active_vertex(int num_vertex);
    int get_active_vertex() const;
    QVector<qint16> get_events_vertex(int number_vertex) const;

private:
    Matrix event_matrix_;
    int active_vertex;
    std::weak_ptr<GraphWindow> graphWindow_;
};
