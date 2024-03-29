#include "notice.hpp"

#include <QPainter>
#include <QApplication>

#include <QScreen>
#include <QDebug>

Notice::Notice(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    animation.setTargetObject(this);
    animation.setPropertyName("popupOpacity");
    connect(&animation, &QAbstractAnimation::finished, this, &Notice::hide);

    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label.setStyleSheet("QLabel {"
                        "color: white;"
                        "margin-top: 3px;"
                        "margin-bottom: 3px;"
                        "margin-left: 6px;"
                        "margin-right: 6px;}");

    layout.addWidget(&label, 0, 0);
    setLayout(&layout);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Notice::hideAnimation);
}

void Notice::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(notice_color_));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);
}

void Notice::setProperties(const QColor& notice_color,
                           const QString &text)
{
    notice_color_ = notice_color;
    label.setText(text);
    adjustSize();
}

void Notice::show()
{
    setWindowOpacity(0.0);
    animation.setDuration(150);
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);

    setFixedSize(width(), height());
    QWidget::show();

    animation.start();
    timer->start(1500);
}

void Notice::hideAnimation()
{
    timer->stop();
    animation.setDuration(1000);
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);
    animation.start();
}

void Notice::hide()
{
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void Notice::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float Notice::getPopupOpacity() const
{
    return popupOpacity;
}
