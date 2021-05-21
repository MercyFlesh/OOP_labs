#include "graph.hpp"
#include  <QDebug>


Graph::Graph(Matrix matrix)
    : matrix_(std::move(matrix)),
      count_vertices(matrix_.size())
{
}


void Graph::update(Matrix matrix)
{
    matrix_ = std::move(matrix);
    count_vertices = matrix_.size();
}


void Graph::set_graph_window(std::weak_ptr<GraphWindow> graphWindow)
{
    graphWindow_ = std::move(graphWindow);
}

int Graph::get_count_vertices() const
{
    return matrix_.size();
}


Matrix Graph::get_matrix() const
{
    return matrix_;
}


QPoint Graph::find_point(QPoint start, QPoint end, qreal r) const
{
    qreal line_a = end.y() - start.y();
    qreal line_b = start.x() - end.x();
    qreal line_c = (-start.x() * (end.y() - start.y())) -
              (-start.y() * (end.x() - start.x()));

    qreal x_0 = start.x();
    qreal y_0 = start.y();
    qreal k = -line_a/line_b;
    qreal b = -line_c/line_b;

    qreal d = pow(2*k*b - 2*x_0 - 2*y_0*k, 2) -
            (4 * (1 + pow(k, 2)) * (pow(b, 2) - pow(r, 2) + pow(x_0, 2) + pow(y_0, 2) - 2*y_0*b));

    if (d > 0)
    {
        qreal x1 = (-(2*k*b - 2*x_0-2*y_0*k) - sqrt(d))/(2 * (1 + pow(k, 2)));
        qreal x2 = (-(2*k*b - 2*x_0-2*y_0*k) + sqrt(d))/(2 * (1 + pow(k, 2)));

        if (start.x() < end.x())
        {
            if (start.x() < x1)
                return QPoint(x1, k * x1 + b);
            else
                return QPoint(x2, k * x2 + b);
        }
        else
        {
            if (start.x() > x1)
                return QPoint(x1, k * x1 + b);
            else
                return QPoint(x2, k * x2 + b);
        }
    }
}


void Graph::draw(QPainter* p, QRect r, QColor c)
{
    qreal cw = 0.5*r.width();
    qreal ch = 0.5*r.height();
    qreal cr = 0.9*(cw>ch?ch:cw);
    qreal a = 2.0*acos(-1.0)/count_vertices;
    QFont font;
    font.setBold(true);

    p->setPen(QPen(Qt::black));
    p->setBrush(QBrush(c));
    p->setFont(font);

    std::vector<QPoint> t(count_vertices);
    for (std::size_t i = 0; i < t.size(); i++)
    {
        t[i] = QPoint(cw+cr*sin(i*a), ch-cr*cos(i*a));
        p->drawEllipse(t[i], 10, 10);
        p->drawText(QRect(t[i].x() - 7, t[i].y() - 7, 15, 15),
                    QString().setNum(i), QTextOption(Qt::AlignCenter));
    }

    p->setPen(QPen((Qt::black), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p->setBrush((Qt::black));
    QPointF head, arrowP1, arrowP2;
    double angle;
    qreal arrowSize = 10;
    for (std::size_t i = 0; i < matrix_.size(); ++i)
    {
        for (std::size_t j = 0; j < matrix_[i].size(); ++j)
        {
            if ((i == j) && (matrix_[i][j] == 1))
            {
                if (t[i].x() >= r.size().width() / 2 && t[i].y() < r.size().height() / 2)
                {
                    angle = 1.07 * M_PI;
                    head = QPoint(t[i].x() + 10, t[i].y());

                    p->drawArc(t[i].x(), t[i].y() - 27, 25, 25, 16 * - 70, 16 * 270);
                }
                else if (t[i].x() > r.size().width() / 2 && t[i].y() >= r.size().height() / 2)
                {
                    angle = 0.57 * M_PI;
                    head = QPoint(t[i].x(), t[i].y() + 10);

                    p->drawArc(t[i].x(), t[i].y(), 25, 25, 16 * - 180, 16 * 270);
                }
                else if (t[i].x() <= r.size().width() / 2 && t[i].y() > r.size().height() / 2)
                {
                    angle = 0.1 * M_PI;
                    head = QPoint(t[i].x() - 10, t[i].y());

                    p->drawArc(t[i].x() - 25, t[i].y(), 25, 25, 16 * - 270, 16 * 270);
                }
                else if (t[i].x() < r.size().width() / 2 && t[i].y() <= r.size().height() / 2)
                {
                    angle = 1.57 * M_PI;
                    head = QPoint(t[i].x(), t[i].y() - 10);

                    p->drawArc(t[i].x() - 25, t[i].y() - 25, 25, 25, 16 * - 360, 16 * 270);
                }

            }
            else if (matrix_[i][j] == 1)
            {
                QPoint start_peak = find_point(t[i], t[j], 10);
                QPoint end_peak = find_point(t[j], t[i], 10);
                QLineF line(start_peak, end_peak);

                angle = std::atan2(-line.dy(), line.dx());
                head = line.p2();

                p->drawLine(line);
            }

            arrowP1 = head - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                      cos(angle + M_PI / 3) * arrowSize);
            arrowP2 = head - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                      cos(angle + M_PI - M_PI / 3) * arrowSize);

            p->drawPolygon(QPolygonF() << head << arrowP2 << arrowP1);
        }
    }
}
