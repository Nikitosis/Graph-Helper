#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QThread>
#include <QVector>
#include <QStack>
#include <SceneElements/graph.h>
#include <QMutexLocker>

class Algorithm : public QObject
{
    Q_OBJECT
public:
    Algorithm(QMutex *mtx, Graph *graph, bool *isExit);
    Algorithm();
    void runDFS(int startEdge);
    void setStartEdge(int edge);

public slots:
    void runAlgo();

signals:
    void updateDfs(QVector<QVector<int>> Matrix, QVector<bool> Visited, QVector<int> Stack);
    void changeBridgeColor(int startEdgeId, int endEdgeId,QColor color);
    void changeEdgeColor(int id,QColor color);
    void lockLine(int codeLineIndex);

private:
    QMutex *_mtx;
    const Graph _graph;
    bool * _isExit;
    int _startEdge;

};

#endif // ALGORITHM_H
