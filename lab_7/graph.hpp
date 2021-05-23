#pragma once

#include <QVector>
#include <QPainter>
#include <vector>
#include <utility>

//#include "matrix.hpp"

using Matrix = QVector<QVector<qint16>>;


class Graph
{
public:
    Graph(Matrix matrix);
    void draw(QPainter* p, QRect r, QColor c);
    int get_count_vertices() const;
    Matrix get_matrix() const;
    QVector<QPoint> get_vertices_pos() const;
    QPoint get_vertex_pos(int number_vertex) const;
    void update(Matrix matrix);

private:
    QPoint find_point(QPoint start, QPoint end, qreal r) const;

private:
    Matrix transition_matrix_;
    QVector<QPoint> vertices_pos;
    int count_vertices;
};
