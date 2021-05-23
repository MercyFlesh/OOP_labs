#pragma once

#include <QWidget>
#include <QPainter>

#include <memory>

#include "state_graph.hpp"

class StateGraph;

class GraphWindow : public QWidget
{
public:
    explicit GraphWindow(QWidget* parent = nullptr);
    void set_graph(std::weak_ptr<StateGraph> graph);
    ~GraphWindow() = default;

public slots:
    void paintEvent(QPaintEvent* event) override;

private:
    std::weak_ptr<StateGraph> graph_ptr;
};
