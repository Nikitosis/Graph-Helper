#include "visualgraphsceneview.h"

VisualGraphSceneView::VisualGraphSceneView(QWidget *parent) : QGraphicsView(parent)
{
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,1000);

    this->setScene(scene);
    this->setMouseTracking(true);               //for mouse move event

    graph=new Graph(this);
    curBridge=nullptr;
    line=nullptr;
    makingBridge=false;
    curEdgeEditProxy=nullptr;
    curBridgeEditProxy=nullptr;

    //update optimization.Update viewport every 17 ms
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this->viewport(),SLOT(update()));
    timer->start(17);


    horizontalScrollBar()->setHidden(true);         //hide scrollbars
    verticalScrollBar()->setHidden(true);
}


void VisualGraphSceneView::setMode(Mode mode)
{
    if(nowMode==CursorMode)
    {
        graph->setEdgeMovable(false);       //user can't move Edge
    }

    nowMode=mode;

    if(nowMode==CursorMode)
    {
        graph->setEdgeMovable(true);                //user can move edge
    }
}

void VisualGraphSceneView::deleteAll()
{
    graph->deleteAll();
}

void VisualGraphSceneView::deleteProxys(QMouseEvent *event)        //delete proxys if they are not deleted
{
    if(curEdgeEditProxy!=nullptr)
    {
        QGraphicsProxyWidget *edgeEdit=dynamic_cast<QGraphicsProxyWidget *>(itemAt(event->pos()));
        if(!edgeEdit)
        {
            delete curEdgeEditProxy;
            curEdgeEditProxy=nullptr;
        }
    }
    if(curBridgeEditProxy!=nullptr)
    {
        QGraphicsProxyWidget *BridgeEdit=dynamic_cast<QGraphicsProxyWidget *>(itemAt(event->pos()));
        if(!BridgeEdit)
        {
            delete curBridgeEditProxy;
            curBridgeEditProxy=nullptr;
        }
    }
}

QVector<QVector<int> > VisualGraphSceneView::getCorrectMatrix() const
{
    graph->updateBridges();
    return graph->getCorrectMatrix();
}

QVector<MyEdge *> VisualGraphSceneView::getEdges() const
{
    return graph->getEdges();
}

Graph *VisualGraphSceneView::getGraph() const
{
    return graph;
}

QGraphicsScene *VisualGraphSceneView::getScene() const
{
    return scene;
}



void VisualGraphSceneView::mousePressEvent(QMouseEvent *event)//emits the SLOT,which matches the mode
{
    if(event->buttons() & Qt::MidButton)
        emit mousePressMiddleButton(event);

    if(event->buttons() & Qt::LeftButton)
    {
        switch(nowMode)
        {
            case EdgeMode:{emit mousePressEdgeMode(event);break;}
            case BridgeMode:{emit mousePressBridgeMode(event);break;}
            case BridgeDeleteMode:{emit mousePressDeleteBridgeMode(event);break;}
        }
    }

    deleteProxys(event);

    if((event->buttons() & Qt::RightButton) && !(event->buttons() & Qt::LeftButton))
    {
        switch(nowMode)
        {
            case CursorMode:{emit mouseRightClickCursorMode(event);break;}
        }
    }

    QGraphicsView::mousePressEvent(event);                  //to let children's elements get this event
}

void VisualGraphSceneView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos=mapToScene(event->pos());
    qDebug()<<"Move"<<pos.x()<<" "<<pos.y();
    if(event->buttons() & Qt::MidButton)
        emit mouseMoveMiddleButton(event);

    if(nowMode==BridgeMode)
        emit mouseMoveBridgeMode(event);

    QGraphicsView::mouseMoveEvent(event);
}


void VisualGraphSceneView::mouseMoveBridgeMode(QMouseEvent *event)       //move mouse in Bridge mode
{
    if(makingBridge)                               //if we are making bridge
    {
        QPointF pos=mapToScene(event->pos());
        MyEdge *edge=curBridge->getStartEdge();

        if(line==nullptr)
            line=new Line(edge->getCordinates().x(),edge->getCordinates().y(),pos.x(),pos.y(),this);

        line->setCoords(edge->getCordinates().x(),edge->getCordinates().y(),pos.x(),pos.y());
        if(!scene->items().contains(line))              //to not add line twice
            scene->addItem(line);
    }
}



void VisualGraphSceneView::mousePressEdgeMode(QMouseEvent *event)
{
    QPointF pos=mapToScene(event->pos());
    QRectF sceneRect=scene->sceneRect();
    if(pos.x()>=sceneRect.x() && pos.x()<=sceneRect.width() && pos.y()>=sceneRect.y() && pos.y()<=sceneRect.height())           //check if user clicked out of the scene
        if(event->buttons() & Qt::LeftButton)
        {
            const int radius=20;
            MyEdge *edge=new MyEdge(pos.x()-radius,pos.y()-radius,radius,QString::number(graph->getFreeId()+1),graph->getFreeId());
            //configuration edge
            connect(edge,SIGNAL(mousePressSignal(QGraphicsSceneMouseEvent*)),this,SLOT(mousePressEdge(QGraphicsSceneMouseEvent*)));
            edge->setFlag(QGraphicsItem::ItemSendsGeometryChanges);         //enable onChange slot(while moving Edge)

            scene->addItem(edge);
            graph->addEdge(edge);
        }
}


void VisualGraphSceneView::mousePressDeleteBridgeMode(QMouseEvent *event)
{
    QPointF pos=mapToScene(event->pos());
    Bridge *closest=graph->findClosest(pos);
    const int maxLen=20;
    if(closest!=nullptr && graph->getLen(closest,pos)<maxLen)
    {
        graph->deleteBridge(closest);
    }
}

void VisualGraphSceneView::mousePressBridgeMode(QMouseEvent *event)
{
    if(line!=nullptr)        //if we clicked second time,using bridge-making,we delete line
    {
        delete line;
        line=nullptr;
    }

    MyEdge *edge=dynamic_cast<MyEdge*>(itemAt(event->pos()));               //find object,we clicked on
    if(!edge)                //if we didn't click on edge
        {
            delete curBridge;
            curBridge=nullptr;

            if(!makingBridge)               //if we are not making bridge,we find closest bridge and if
            {                                           //length between this bridge and click position is small,then we change bridge mode
                QPointF pos=mapToScene(event->pos());
                Bridge *closest=graph->findClosest(pos);
                const int maxLen=20;
                if(closest!=nullptr && graph->getLen(closest,pos)<maxLen)
                {
                    closest->changeConnectMode();      //change direction of the Bridge
                    graph->changeConnectMode(closest);
                }
            }
            makingBridge=false;
        }
}

void VisualGraphSceneView::mousePressMiddleButton(QMouseEvent *event)
{
    originPosX=event->x();
    originPosY=event->y();
}

void VisualGraphSceneView::mouseMoveMiddleButton(QMouseEvent *event)  //move scene with mid button
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-(event->x()-originPosX));
    verticalScrollBar()->setValue(verticalScrollBar()->value()-(event->y()-originPosY));

    originPosX=event->x();
    originPosY=event->y();
}

/*When user double clicked on the edge,we create new EdgeEdit
Firstly,we create curEdgeEdit and give it our edge,we clicked on
then we initialized curEdgeEditProxy and set coordinates of it.*/
void VisualGraphSceneView::mouseRightClickCursorMode(QMouseEvent *event)
{
   MyEdge *edge=dynamic_cast<MyEdge*>(itemAt(event->pos()));
   if(edge)
   {
       EdgeEdit *curEdgeEdit=new EdgeEdit(this);
       curEdgeEdit->setEdge(edge);

       if(curEdgeEditProxy!=nullptr)
       {
           delete curEdgeEditProxy;
           curEdgeEditProxy=nullptr;
       }

      curEdgeEditProxy=getProxyWidget(curEdgeEdit);

       QPointF center=edge->getCordinates();
       QRectF size=curEdgeEditProxy->geometry();
       curEdgeEditProxy->setPos(center.x(),center.y()-size.height()-edge->getRadius());
       curEdgeEditProxy->show();
   }
   else
   {
       QPointF pos=mapToScene(event->pos());
       Bridge* bridge=graph->findClosest(pos);
       const int maxDistance=20;
       if(graph->getLen(bridge,pos)<=maxDistance)
       {
           BridgeEdit *curBridgeEdit=new BridgeEdit(this);
           curBridgeEdit->setBridge(bridge);

           if(curBridgeEditProxy!=nullptr)
           {
               delete curBridgeEditProxy;
               curBridgeEditProxy=nullptr;
           }

           curBridgeEditProxy=getProxyWidget(curBridgeEdit);

           QPointF center=bridge->getCenter();
           QRectF size=curBridgeEdit->geometry();
           curBridgeEditProxy->setPos(center.x(),center.y()-size.height());
           curBridgeEditProxy->show();
       }
   }
}

void VisualGraphSceneView::wheelEvent(QWheelEvent *event)  //scaling scene with wheel
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

void VisualGraphSceneView::mousePressEdge(QGraphicsSceneMouseEvent *event)//When we press Edge
{
    if(nowMode==BridgeMode)
    {
        QObject *snd=QObject::sender();
        MyEdge *edge=qobject_cast<MyEdge*>(snd);
        if(!makingBridge)               //if we are not in making bridge process
        {
            makingBridge=true;
            curBridge=new Bridge(edge);
        }
        else                                //else add our bridge to the graph and scene
        {
            curBridge->setEndEdge(edge);
            curBridge->update();
            graph->addBridge(curBridge);
            scene->addItem(curBridge);
            curBridge=nullptr;
            makingBridge=false;
        }
    }
    if(nowMode==EdgeDeleteMode)
    {
        QObject *snd=QObject::sender();
        MyEdge *edge=qobject_cast<MyEdge*>(snd);
        graph->deleteEdge(edge);
    }
}

QGraphicsProxyWidget *VisualGraphSceneView::getProxyWidget(QWidget *uiElement)
{
    uiElement->setParent(0);
    uiElement->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsProxyWidget *proxy;
    proxy=scene->addWidget(uiElement);
    proxy->setZValue(5000);
    return proxy;
}
