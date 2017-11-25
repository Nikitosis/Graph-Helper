#ifndef MYGRAPHICSSCENEVIEW_H
#define MYGRAPHICSSCENEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QVector>
#include <QPainter>
#include <QScrollBar>
#include <QVector>
#include <QGraphicsProxyWidget>
#include "myedge.h"
#include "mygraphicsscene.h"
#include "graph.h"
#include "bridge.h"
#include "line.h"
#include "edgeedit.h"
#include "bridgeedit.h"



class MyGraphicsSceneView :public QGraphicsView
{
    Q_OBJECT
public:
    enum Mode{CursorMode,BridgeMode,EdgeMode,BridgeDeleteMode,EdgeDeleteMode};
    explicit MyGraphicsSceneView(QWidget *parent = nullptr);

    QVector<QVector<int>> getCorrectMatrix() const;
    QVector<MyEdge*> getEdges() const;
    QGraphicsProxyWidget *getProxyWidget(QWidget *uiElement);

signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void mouseMoveBridgeMode(QMouseEvent *event);
    void mousePressBridgeMode(QMouseEvent *event);
    void mousePressEdgeMode(QMouseEvent *event);
    void mousePressDeleteBridgeMode(QMouseEvent *event);

    void mousePressMiddleButton(QMouseEvent *event); //move scene in view
    void mouseMoveMiddleButton(QMouseEvent *event);

    void mouseRightClickCursorMode(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void mousePressEdge(QGraphicsSceneMouseEvent *event);

    void setMode(Mode mode);
    void deleteAll();

protected:
    void deleteProxys(QMouseEvent *event);
private:
     QGraphicsScene *scene;
     Graph *graph;
     Mode nowMode;
     Bridge *curBridge;
     Line *line;
     QGraphicsProxyWidget *curEdgeEditProxy;
     QGraphicsProxyWidget *curBridgeEditProxy;
     int originPosX;
     int originPosY;
     bool makingBridge;

};

#endif // MYGRAPHICSSCENEVIEW_H
