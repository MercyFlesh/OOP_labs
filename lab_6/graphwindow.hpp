#pragma once

#include <QWidget>
#include <QPainter>

#include <memory>

#include "graph.hpp"

class Graph;

class GraphWindow : public QWidget
{
    //Q_OBJECT

public:
    explicit GraphWindow(QWidget* parent = nullptr);
    void set_graph(std::weak_ptr<Graph> graph);
    ~GraphWindow() = default;

public slots:
    void paintEvent(QPaintEvent* event) override;

private:
    std::weak_ptr<Graph> graph_ptr;
};
