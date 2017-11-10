#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QVector>

#include "myedge.h"
#include "bridge.h"
#include "myedge.h"

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);

    void addBridge(Bridge *bridge);
    void addEdge(MyEdge *edge);
    void changeConnectMode(Bridge *bridge);
    void setEdgeMovable(bool isMovable);
    void updateBridges();

    int getEdgesAmount() const;
    Bridge *findClosest(QPointF &point) const;
    double getLen(Bridge *bridge,QPointF &point) const;

    void deleteEdge(MyEdge *edge);

signals:

public slots:

protected:
private:
    QVector<QVector<int>> _Matrix;
    QVector<Bridge*> _Bridges;
    QVector<MyEdge*> _Edges;
    int _edgesAmount;
};

#endif // GRAPH_H
