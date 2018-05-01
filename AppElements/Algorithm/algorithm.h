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
    Algorithm(QMutex *mtx, Graph *graph, bool &isExit,QWaitCondition *condit);
    void runDFS(int startEdge);
    void setStartEdge(int edge);
protected:
    void lockLine(int codeLineIndex);
    void updateDfs(QVector<QVector<int> > Matrix, QVector<bool> Visited, QVector<int> Stack);

public slots:
    void runAlgo();

signals:
    void changeBridgeColor(int startEdgeId, int endEdgeId,QColor color);
    void changeEdgeColor(int id,QColor color);
    void updateEditor(int codeLineIndex);
    void handleSignals();
    void watchSaveState();
    void watchClear();
    void watchAddTwoDArray(QVector<QVector<QString> >,QVector<QString>,QVector<QString>,QString);
    void watchAddOneDArray(QVector<QString>,QVector<QString>,QString);
    void watchResetState();

private:
    QWaitCondition *_condit;
    QMutex *_mtx;
    const Graph _graph;
    bool & _isExit;
    int _startEdge;

};

#endif // ALGORITHM_H
