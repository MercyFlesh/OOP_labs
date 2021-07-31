#include "graphwindow.hpp"

#include <QDebug>


GraphWindow::GraphWindow(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
}


void GraphWindow::paintEvent(QPaintEvent* event)
{
    if (auto graph = graph_ptr.lock())
    {
        Q_UNUSED(event);
        QPainter painter(this);
        graph->draw(&painter, rect(), Qt::green);
    }
}


void GraphWindow::set_graph(std::weak_ptr<Graph> graph)
{
    graph_ptr = std::move(graph);
}
