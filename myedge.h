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
    explicit MyEdge(int x, int y, int radius, QString info, int id, QObject *parent = nullptr);
    explicit MyEdge(QPointF p,int radius,QString info,int id,QObject *parent = nullptr);
    int getId() const;
    double getRadius() const;
    QPointF getCordinates() const;
    QString getInfo() const;
    void setInfo(QString info);

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
    int _x;
    int _y;
    int _radius;
    int _id;
    QString _info;
    int _xStart,_yStart;
};

#endif // MYEDGE_H
