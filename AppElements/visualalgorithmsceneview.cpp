#include "visualalgorithmsceneview.h"

VisualAlgorithmSceneView::VisualAlgorithmSceneView(QWidget *parent) : QGraphicsView(parent)
{
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,1000);
    this->setScene(scene);
    horizontalScrollBar()->setHidden(true);
    verticalScrollBar()->setHidden(true);
    setMouseTracking(true); //for mouse move events

    //update optimization.Update viewport every 17 ms
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this->viewport(),SLOT(update()));
    timer->start(17);
}

void VisualAlgorithmSceneView::addElement(QGraphicsItem *element)
{
    scene->addItem(element);
}

QGraphicsScene *VisualAlgorithmSceneView::getScene() const
{
    return scene;
}

void VisualAlgorithmSceneView::wheelEvent(QWheelEvent *event)
{
    const double scaleFactor = 1.15;
    if(event->delta() > 0)
       {
           // Zoom in
           scale(scaleFactor, scaleFactor);
       }
    else
       {
           // Zooming out
           scale(1.0 / scaleFactor, 1.0 / scaleFactor);

           double k=this->transform().m11(); //check if we went out of sceneRect
           if(this->width()*(1.0/k)>scene->width())//if we went out,then approximate
              scale(scaleFactor, scaleFactor);
    }
}

void VisualAlgorithmSceneView::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::MiddleButton)
        emit mousePressMiddleButton(event);
}

void VisualAlgorithmSceneView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::MiddleButton)
        emit mouseMoveMiddleButton(event);
}

void VisualAlgorithmSceneView::mousePressMiddleButton(QMouseEvent *event)
{
    originPosX=event->x();
    originPosY=event->y();
}

void VisualAlgorithmSceneView::mouseMoveMiddleButton(QMouseEvent *event)
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-(event->x()-originPosX));
    verticalScrollBar()->setValue(verticalScrollBar()->value()-(event->y()-originPosY));

    originPosX=event->x();
    originPosY=event->y();
}
