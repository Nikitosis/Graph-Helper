#include "mygraphicssceneview.h"

MyGraphicsSceneView::MyGraphicsSceneView(QWidget *parent) : QGraphicsView(parent)
{
    scene=new QGraphicsScene;
    scene->setSceneRect(0,0,1000,1000);
    this->setScene(scene);
    this->setMouseTracking(true);//for mouse move event

    graph=new Graph(this);
    curBridge=nullptr;
    line=nullptr;


    horizontalScrollBar()->setHidden(true);//hide scrollbars
    verticalScrollBar()->setHidden(true);
}


void MyGraphicsSceneView::setMode(Mode mode)
{
    if(nowMode==CursorMode)
    {
        graph->setEdgeMovable(false);//user can't move Edge
    }

    nowMode=mode;

    if(nowMode==CursorMode)
    {
        graph->setEdgeMovable(true);//user can move edge
    }
}

QVector<QVector<int> > MyGraphicsSceneView::getCorrectMatrix() const
{
    return graph->getCorrectMatrix();
}

QVector<MyEdge *> MyGraphicsSceneView::getEdges() const
{
    return graph->getEdges();
}



void MyGraphicsSceneView::mousePressEvent(QMouseEvent *event)//emits the SLOT,which matches the mode
{
    if(event->buttons() & Qt::MidButton)
        emit mousePressMiddleButton(event);

    if((event->buttons() & (Qt::LeftButton | Qt::RightButton)))
    {
        switch(nowMode)
        {
            case EdgeMode:{emit mousePressEdgeMode(event);break;}
            case BridgeMode:{emit mousePressBridgeMode(event);break;}
            case BridgeDeleteMode:{emit mousePressDeleteEdgeMode(event);break;}
        }
    }
    QGraphicsView::mousePressEvent(event);//to let children's elements get this event
}

void MyGraphicsSceneView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos=mapToScene(event->pos());
    qDebug()<<"Move"<<pos.x()<<" "<<pos.y();
    if(event->buttons() & Qt::MidButton)
        emit mouseMoveMiddleButton(event);

    if(nowMode==BridgeMode)
        emit mouseMoveBridgeMode(event);

    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsSceneView::mouseMoveBridgeMode(QMouseEvent *event)
{
    if(curBridge!=nullptr) //if we are making bridge
    {
        QPointF pos=mapToScene(event->pos());
        MyEdge *edge=curBridge->getStartEdge();

        if(line==nullptr)
            line=new Line(edge->getCordinates().x(),edge->getCordinates().y(),pos.x(),pos.y());

        line->setCoords(edge->getCordinates().x(),edge->getCordinates().y(),pos.x(),pos.y());
        if(!scene->items().contains(line))  //to not add line twice
            scene->addItem(line);
    }
}



void MyGraphicsSceneView::mousePressEdgeMode(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF pos=mapToScene(event->pos());
        const int radius=20;
        MyEdge *edge=new MyEdge(pos.x()-radius,pos.y()-radius,radius,QString::number(graph->getFreeId()+1),graph->getFreeId());
        //configuration edge
        connect(edge,SIGNAL(mousePressSignal(QGraphicsSceneMouseEvent*)),this,SLOT(mousePressEdge(QGraphicsSceneMouseEvent*)));
        connect(edge,SIGNAL(edgeMoved(MyEdge*)),this,SLOT(edgeMoved(MyEdge*)));
        edge->setFlag(QGraphicsItem::ItemSendsGeometryChanges);//enable onChange slot(while moving Edge)

        scene->addItem(edge);
        graph->addEdge(edge);
    }
}

void MyGraphicsSceneView::mousePressDeleteEdgeMode(QMouseEvent *event)
{
    QPointF pos=mapToScene(event->pos());
    Bridge *closest=graph->findClosest(pos);
    const int maxLen=20;
    if(closest!=nullptr && graph->getLen(closest,pos)<maxLen)
    {
        graph->deleteBridge(closest);
    }
}

void MyGraphicsSceneView::mousePressBridgeMode(QMouseEvent *event)
{
    bool wasLine=false;
    if(line!=nullptr)        //if we clicked second time,using bridge-making,we delete line
    {
        delete line;
        line=nullptr;
        wasLine=true;
    }

    MyEdge *edge=dynamic_cast<MyEdge*>(itemAt(event->pos()));
    if(!edge)                //if we didn't click on edge
        {
            delete curBridge;
            curBridge=nullptr;

            if(line==nullptr && !wasLine)//if we are not using line(bridge making),we find closest bridge and if
            {                //length between this bridge and click position is small,then we change bridge mode
                QPointF pos=mapToScene(event->pos());
                Bridge *closest=graph->findClosest(pos);
                const int maxLen=20;
                if(closest!=nullptr && graph->getLen(closest,pos)<maxLen)
                {
                    closest->changeConnectMode();      //change direction of the Bridge
                    graph->changeConnectMode(closest);
                }
            }
        }
}

void MyGraphicsSceneView::mousePressMiddleButton(QMouseEvent *event)
{
    originPosX=event->x();
    originPosY=event->y();
}

void MyGraphicsSceneView::mouseMoveMiddleButton(QMouseEvent *event)  //move scene with mid button
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-(event->x()-originPosX));
    verticalScrollBar()->setValue(verticalScrollBar()->value()-(event->y()-originPosY));

    originPosX=event->x();
    originPosY=event->y();
}

void MyGraphicsSceneView::wheelEvent(QWheelEvent *event)  //scaling scene with wheel
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

void MyGraphicsSceneView::mousePressEdge(QGraphicsSceneMouseEvent *event)//When we press Edge
{
    if(nowMode==BridgeMode)
    {
        QObject *snd=QObject::sender();
        MyEdge *edge=qobject_cast<MyEdge*>(snd);
        if(curBridge==nullptr)//if we have not chosen first point
        {
            curBridge=new Bridge(edge);
        }
        else
        {
            curBridge->setEndEdge(edge);
            curBridge->update();
            graph->addBridge(curBridge);
            scene->addItem(curBridge);

            curBridge=nullptr;
        }
    }
    if(nowMode==EdgeDeleteMode)
    {
        QObject *snd=QObject::sender();
        MyEdge *edge=qobject_cast<MyEdge*>(snd);
        graph->deleteEdge(edge);
    }
}
