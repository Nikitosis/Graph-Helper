#include "visualgraphsceneview.h"

VisualGraphSceneView::VisualGraphSceneView(QWidget *parent) : QGraphicsView(parent)
{
    _scene=new QGraphicsScene(this);
    _scene->setSceneRect(0,0,1000,1000);

    _graph=new Graph(this);
    _line=nullptr;
    _makingBridge=false;
    _curEdgeEditProxy=nullptr;
    _curBridgeEditProxy=nullptr;

    this->setScene(_scene);
    this->setMouseTracking(true);               //for mouse move event
    this->setMode(Mode::EdgeMode);


    //update optimization.Update viewport every 17 ms
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    _timer=new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this->viewport(),SLOT(update()));
    _timer->start(17);


    horizontalScrollBar()->setHidden(true);         //hide scrollbars
    verticalScrollBar()->setHidden(true);
}


void VisualGraphSceneView::setMode(Mode mode)
{
    _nowMode=mode;
    _graph->setEdgeMovable(_nowMode==CursorMode);                //user can move edge
}

void VisualGraphSceneView::deleteAll()
{
    _graph->deleteAll();
}

void VisualGraphSceneView::deleteProxys(QMouseEvent *event)        //delete proxys,when we click(but not on them)
{
    if(_curEdgeEditProxy!=nullptr)
    {
        QGraphicsProxyWidget *edgeEdit=dynamic_cast<QGraphicsProxyWidget *>(itemAt(event->pos()));
        if(!edgeEdit)
        {
            delete _curEdgeEditProxy;
            _curEdgeEditProxy=nullptr;
        }
    }
    if(_curBridgeEditProxy!=nullptr)
    {
        QGraphicsProxyWidget *BridgeEdit=dynamic_cast<QGraphicsProxyWidget *>(itemAt(event->pos()));
        if(!BridgeEdit)
        {
            delete _curBridgeEditProxy;
            _curBridgeEditProxy=nullptr;
        }
    }
}

QVector<QVector<int> > VisualGraphSceneView::getCorrectMatrix() const
{
    _graph->updateBridges();
    return _graph->getCorrectMatrix();
}

QVector<MyEdge *> VisualGraphSceneView::getEdges() const
{
    return _graph->getEdges();
}

Graph *VisualGraphSceneView::getGraph() const
{
    return _graph;
}

QGraphicsScene *VisualGraphSceneView::getScene() const
{
    return _scene;
}



void VisualGraphSceneView::mousePressEvent(QMouseEvent *event)//emits the SLOT,which matches the mode
{
    deleteProxys(event);
    if(event->buttons() & Qt::MidButton)
        emit mousePressMiddleButton(event);

    if(event->buttons() & Qt::LeftButton)
    {
        switch(_nowMode)
        {
            case EdgeMode:{emit mousePressEdgeMode(event);break;}
            case BridgeMode:{emit mousePressBridgeMode(event);break;}
            case BridgeDeleteMode:{emit mousePressDeleteBridgeMode(event);break;}
        }
    }


    if((event->buttons() & Qt::RightButton) && !(event->buttons() & Qt::LeftButton))
    {
        switch(_nowMode)
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

    if(_nowMode==BridgeMode && _makingBridge)
        emit mouseMoveBridgeMode(event);

    QGraphicsView::mouseMoveEvent(event);
}


void VisualGraphSceneView::mouseMoveBridgeMode(QMouseEvent *event)       //move mouse in Bridge mode
{
    QPointF pos=mapToScene(event->pos());
    MyEdge *edge=firstBridgeEdge;

    if(_line==nullptr)
        _line=new Line(edge->getCordinates().x(),edge->getCordinates().y(),pos.x(),pos.y(),this);

    _line->setCoords(edge->getCordinates().x(),edge->getCordinates().y(),pos.x(),pos.y());
    if(!_scene->items().contains(_line))              //to not add line twice
        _scene->addItem(_line);
}



void VisualGraphSceneView::mousePressEdgeMode(QMouseEvent *event)
{
    QPointF pos=mapToScene(event->pos());
    QRectF sceneRect=_scene->sceneRect();
    if(pos.x()>=sceneRect.x() && pos.x()<=sceneRect.width() && pos.y()>=sceneRect.y() && pos.y()<=sceneRect.height())           //check if user haven't clicked out of the scene
        if(event->buttons() & Qt::LeftButton)
        {
            const int radius=20;
            MyEdge *edge=new MyEdge(pos.x()-radius,pos.y()-radius,radius,QString::number(_graph->getFreeEdgeId()+1),_graph->getFreeEdgeId());
            //configuration edge
            connect(edge,SIGNAL(mousePressSignal(QGraphicsSceneMouseEvent*)),this,SLOT(mousePressEdge(QGraphicsSceneMouseEvent*)));
            edge->setFlag(QGraphicsItem::ItemSendsGeometryChanges);         //enable onChange slot(while moving Edge)

            _scene->addItem(edge);
            _graph->addEdge(edge);
        }
}


void VisualGraphSceneView::mousePressDeleteBridgeMode(QMouseEvent *event)
{
    QPointF pos=mapToScene(event->pos());
    Bridge *closest=_graph->findClosest(pos);
    const int maxLen=20;
    if(closest!=nullptr && _graph->getLen(closest,pos)<maxLen)  //delete our bridge it length between click and bridge less than maxLen
    {
        _graph->deleteBridge(closest);
    }
}

void VisualGraphSceneView::mousePressBridgeMode(QMouseEvent *event)
{
    if(_line!=nullptr)        //if we clicked second time,using bridge-making,we delete line
    {
        delete _line;
        _line=nullptr;
    }

    MyEdge *edge=dynamic_cast<MyEdge*>(itemAt(event->pos()));               //find object,we clicked on
    if(!edge)                //if we didn't click on edge
        {
            if(!_makingBridge)               //if we are not making bridge,we find closest bridge and if
            {                                           //length between this bridge and click position is small,then we change bridge mode
                QPointF pos=mapToScene(event->pos());
                Bridge *closest=_graph->findClosest(pos);
                const int maxLen=20;
                if(closest!=nullptr && _graph->getLen(closest,pos)<maxLen)
                {
                    closest->changeConnectMode();      //change direction of the Bridge
                    _graph->changeConnectMode(closest);
                }
            }
            _makingBridge=false;
        }
}

void VisualGraphSceneView::mousePressMiddleButton(QMouseEvent *event)
{
    _originPosX=event->x();
    _originPosY=event->y();
}

void VisualGraphSceneView::mouseMoveMiddleButton(QMouseEvent *event)  //move scene with mid button
{
    horizontalScrollBar()->setValue(horizontalScrollBar()->value()-(event->x()-_originPosX));
    verticalScrollBar()->setValue(verticalScrollBar()->value()-(event->y()-_originPosY));

    _originPosX=event->x();
    _originPosY=event->y();
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

      _curEdgeEditProxy=getProxyWidget(curEdgeEdit);

       QPointF center=edge->getCordinates();
       QRectF size=_curEdgeEditProxy->geometry();
       _curEdgeEditProxy->setPos(center.x(),center.y()-size.height()-edge->getRadius());
       _curEdgeEditProxy->show();
   }
   else
   {
       QPointF pos=mapToScene(event->pos());
       Bridge* bridge=_graph->findClosest(pos);
       const int maxDistance=20;
       if(_graph->getLen(bridge,pos)<=maxDistance)
       {
           BridgeEdit *curBridgeEdit=new BridgeEdit(this);
           curBridgeEdit->setBridge(bridge);

           _curBridgeEditProxy=getProxyWidget(curBridgeEdit);

           QPointF center=bridge->getCenter();
           QRectF size=curBridgeEdit->geometry();
           _curBridgeEditProxy->setPos(center.x(),center.y()-size.height());
           _curBridgeEditProxy->show();
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
            if(this->width()*(1.0/k)>_scene->width())//if we went out,then approximate
               scale(scaleFactor, scaleFactor);
        }
}

void VisualGraphSceneView::mousePressEdge(QGraphicsSceneMouseEvent *event)//When we press Edge
{
    QObject *snd=QObject::sender();
    MyEdge *edge=qobject_cast<MyEdge*>(snd);
    if(_nowMode==BridgeMode)
    {
        if(!_makingBridge)               //if we are not in making bridge process
        {
            firstBridgeEdge=edge;
            _makingBridge=true;
        }
        else                                //else add our bridge to the graph and scene
        {
            Bridge *bridge=new Bridge(_graph->getFreeBridgeId(),firstBridgeEdge,edge,this);
            _graph->addBridge(bridge);
            _scene->addItem(bridge);
            _makingBridge=false;
        }
    }
    if(_nowMode==EdgeDeleteMode)
    {
        _graph->deleteEdge(edge);
    }
}

QGraphicsProxyWidget *VisualGraphSceneView::getProxyWidget(QWidget *uiElement)
{
    uiElement->setParent(0);
    uiElement->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsProxyWidget *proxy;
    proxy=_scene->addWidget(uiElement);
    proxy->setZValue(5000);
    return proxy;
}
