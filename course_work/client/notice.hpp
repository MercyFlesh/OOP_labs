#pragma once

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>


class Notice : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;

public:
    explicit Notice(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void setProperties(const QColor& notice_color,
                       const QString& text);
    void show();

private slots:
    void hideAnimation();
    void hide();

private:
    QLabel label;
    QColor notice_color_;
    QGridLayout layout;
    QPropertyAnimation animation;
    float popupOpacity;
    QTimer* timer;
};
