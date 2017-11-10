#ifndef MYEDGE_H
#define MYEDGE_H

#include <QObject>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QRect>
#include <QColor>
#include <QWidget>

class MyEdge : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit MyEdge(QObject *parent = nullptr);
    explicit MyEdge(int x,int y,int radius,int num,QObject *parent = nullptr);
    explicit MyEdge(QPointF p,int radius,int num,QObject *parent = nullptr);
    int getNum() const;
    double getRadius() const;
    QPointF getCordinates() const;

    QRectF boundingRect() const;


signals:
    void mousePressSignal(QGraphicsSceneMouseEvent *event);
    void edgeMoved(MyEdge *edge);

public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    int x;
    int y;
    int radius;
    int num;
    int xStart,yStart;
};

#endif // MYEDGE_H
