#include "mygraphicsscene.h"

mygraphicsscene::mygraphicsscene(QGraphicsScene *parent) : QGraphicsScene(parent)
{
    this->setSceneRect(0,0,500,500);
}

void mygraphicsscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}
