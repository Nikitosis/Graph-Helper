#ifndef VISUALGRAPHSCENEVIEW_H
#define VISUALGRAPHSCENEVIEW_H

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
#include "SceneElements/myedge.h"
#include "SceneElements/graph.h"
#include "SceneElements/bridge.h"
#include "SceneElements/line.h"
#include "Edits/edgeedit.h"
#include "Edits/bridgeedit.h"



class VisualGraphSceneView :public QGraphicsView
{
    Q_OBJECT
public:
    enum Mode{CursorMode,BridgeMode,EdgeMode,BridgeDeleteMode,EdgeDeleteMode};
    explicit VisualGraphSceneView(QWidget *parent = nullptr);

    QVector<QVector<int>> getCorrectMatrix() const;
    QVector<MyEdge*> getEdges() const;
    Graph *getGraph() const;
    QGraphicsScene *getScene() const;
    QGraphicsProxyWidget *getProxyWidget(QWidget *uiElement);
    QTimer *getTimer() const;

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
     QGraphicsScene *_scene;
     Graph *_graph;
     Mode _nowMode;
     MyEdge *firstBridgeEdge;
     Line *_line;
     QGraphicsProxyWidget *_curEdgeEditProxy;
     QGraphicsProxyWidget *_curBridgeEditProxy;
     int _originPosX;
     int _originPosY;
     bool _makingBridge;

     QTimer *_timer; //update optimization

};

#endif // VISUALGRAPHSCENEVIEW_H
