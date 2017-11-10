#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QGraphicsObject>
#include <QPen>
#include <QPainter>
#include <algorithm>
#include <QDebug>

class Line : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Line(QObject *parent = nullptr);
    explicit Line(int startX,int startY,int endX,int endY,QObject *parent = nullptr);

    QRectF boundingRect() const;

    void setCoords(int x1,int y1,int x2,int y2);

signals:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:

private:
    int startX,startY,endX,endY;
};

#endif // LINE_H
