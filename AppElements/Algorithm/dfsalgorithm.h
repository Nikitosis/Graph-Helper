#ifndef DFSALGORITHM_H
#define DFSALGORITHM_H

#include <QThread>
#include <QVector>
#include <QStack>
#include <SceneElements/graph.h>
#include <AppElements/Algorithm/abstractalgorithm.h>
#include <QMutexLocker>

class DfsAlgorithm : public AbstractAlgorithm
{
    Q_OBJECT
public:
    DfsAlgorithm(QMutex *mtx, Graph *graph, bool &isExit,QWaitCondition *condit);
protected:
    void updateDfs(QVector<QVector<int> > Matrix, QVector<bool> Visited, QVector<int> Stack);
    void runDfs(int startEdge);

public slots:
    void runAlgo();

signals:

private:

};
#endif // DFSALGORITHM_H
