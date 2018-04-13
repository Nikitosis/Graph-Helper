#include "visualalgorithmsceneview.h"

VisualAlgorithmSceneView::VisualAlgorithmSceneView(QWidget *parent) : QGraphicsView(parent)
{
    _scene=new QGraphicsScene(this);
    _scene->setSceneRect(0,0,1000,1000);
    this->setScene(_scene);
    horizontalScrollBar()->setHidden(true);
    verticalScrollBar()->setHidden(true);
    setMouseTracking(true); //for mouse move events

    //update optimization.Update viewport every 17 ms
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    _timer=new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this->viewport(),SLOT(update()));
    _timer->start(17);

}

VisualAlgorithmSceneView::~VisualAlgorithmSceneView()
{
  qDebug()<<"delete VisualAlgorithm";
}

void VisualAlgorithmSceneView::addElement(QGraphicsItem *element)
{
    _scene->addItem(element);
}

QGraphicsScene *VisualAlgorithmSceneView::getScene() const
{
    return _scene;
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
           if(this->width()*(1.0/k)>_scene->width())//if we went out,then approximate
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
    _originPosX=event->x();
    _originPosY=event->y();
}

void VisualAlgorithmSceneView::mouseMoveMiddleButton(QMouseEvent *event)
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-(event->x()-_originPosX));
    verticalScrollBar()->setValue(verticalScrollBar()->value()-(event->y()-_originPosY));

    _originPosX=event->x();
    _originPosY=event->y();
    this->viewport()->update();
}

