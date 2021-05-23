#include "graphwindow.hpp"


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

        QFont font;
        font.setBold(true);
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(Qt::yellow));
        painter.setFont(font);
        QPoint active_vertex_pos = graph->get_vertex_pos(graph->get_active_vertex());

        painter.drawEllipse(active_vertex_pos, 10, 10);
        painter.drawText(QRect(active_vertex_pos.x() - 7, active_vertex_pos.y() - 7, 15, 15),
                    QString().setNum(graph->get_active_vertex()+1), QTextOption(Qt::AlignCenter));
    }
}


void GraphWindow::set_graph(std::weak_ptr<StateGraph> graph)
{
    graph_ptr = std::move(graph);
}
