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
#include "myedge.h"
#include "mygraphicsscene.h"
#include "graph.h"
#include "bridge.h"
#include "line.h"



class MyGraphicsSceneView :public QGraphicsView
{
    Q_OBJECT
public:
    enum Mode{CursorMode,BridgeMode,EdgeMode};
    explicit MyGraphicsSceneView(QWidget *parent = nullptr);

signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void mouseMoveBridgeMode(QMouseEvent *event);
    void mousePressBridgeMode(QMouseEvent *event);
    void mousePressEdgeMode(QMouseEvent *event);

    void mousePressMiddleButton(QMouseEvent *event); //move scene in view
    void mouseMoveMiddleButton(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void mousePressEdge(QGraphicsSceneMouseEvent *event);
    void setMode(Mode mode);


private:
     QGraphicsScene *scene;
     Graph *graph;
     Mode nowMode;
     Bridge *curBridge;
     Line *line;
     int originPosX,originPosY;

};

#endif // MYGRAPHICSSCENEVIEW_H
