#include "visualalgorithmsceneview.h"

VisualAlgorithmSceneView::VisualAlgorithmSceneView(QWidget *parent) : QGraphicsView(parent)
{
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,1000);
    this->setScene(scene);
    horizontalScrollBar()->setHidden(true);
    verticalScrollBar()->setHidden(true);
}

void VisualAlgorithmSceneView::addElement(QGraphicsItem *element)
{
    scene->addItem(element);
}
