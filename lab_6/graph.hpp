#pragma once

#include <QVector>
#include <QPainter>
#include <vector>
#include <utility>

#include "graphwindow.hpp"

class GraphWindow;

using Matrix = QVector<QVector<qint16>>;


class Graph
{
public:
    Graph(Matrix matrix);
    void set_graph_window(std::weak_ptr<GraphWindow> graphWindow);
    void draw(QPainter* p, QRect r, QColor c);
    int get_count_vertices() const;
    Matrix get_matrix() const;
    void update(Matrix matrix);

private:
    QPoint find_point(QPoint start, QPoint end, qreal r) const;

private:    
    Matrix matrix_;
    int count_vertices;
    std::weak_ptr<GraphWindow> graphWindow_;
};
