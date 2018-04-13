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
#include <QFont>

class MyEdge : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit MyEdge(QObject *parent = nullptr);
    explicit MyEdge(int x, int y, int radius, QString info, int id, QObject *parent = nullptr);
    explicit MyEdge(QPointF p,int radius,QString info,int id,QObject *parent = nullptr);
    explicit MyEdge(MyEdge *edge,QObject *parent=nullptr);
    ~MyEdge();
    int getId() const;
    double getRadius() const;
    QPointF getCordinates() const;
    QString getInfo() const;
    void setInfo(QString info);
    void setColor(QColor &color);

    QRectF boundingRect() const;

signals:
    void mousePressSignal(QGraphicsSceneMouseEvent *event);

public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QFont getFont(QPainter *painter);

private:
    int _x;
    int _y;
    int _radius;
    int _id;
    QString _info;
    int _xStart,_yStart;
    QColor _color;
};

#endif // MYEDGE_H
