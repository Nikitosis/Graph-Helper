#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include "myedge.h"

class mygraphicsscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit mygraphicsscene(QGraphicsScene *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

signals:

public slots:
};

#endif // MYGRAPHICSSCENE_H
