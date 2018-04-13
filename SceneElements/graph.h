#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QVector>
#include <QSet>

#include "myedge.h"
#include "bridge.h"
#include "myedge.h"

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);
    explicit Graph(Graph *graph,QObject *parent=nullptr);
    ~Graph();

    void addBridge(Bridge *bridge);
    void addEdge(MyEdge *edge);
    void changeConnectMode(Bridge *bridge);
    void setEdgeMovable(bool isMovable);
    void updateBridges();
    void updateBridgeInfo(Bridge *bridge);

    int getFreeEdgeId() const;
    int getFreeBridgeId() const;
    QVector<QVector<int> > getCorrectMatrix() const;
    QVector<MyEdge *> getEdges() const;
    QVector<Bridge *> getBridges() const;
    Bridge *findClosest(QPointF &point) const;

    void deleteEdge(MyEdge *edge);
    void deleteBridge(Bridge *bridge);
    void deleteAll();

    //some help
    double getLen(Bridge *bridge,QPointF &point) const;

signals:

public slots:

protected:
private:
    QVector<QVector<int>> _Matrix;
    QVector<Bridge*> _Bridges;
    QVector<MyEdge*> _Edges;

};

#endif // GRAPH_H
