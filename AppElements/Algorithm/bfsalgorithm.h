#ifndef BFSALGORITHM_H
#define BFSALGORITHM_H

#include <QThread>
#include <QVector>
#include <QStack>
#include <SceneElements/graph.h>
#include <AppElements/Algorithm/abstractalgorithm.h>
#include <QMutexLocker>

class BfsAlgorithm : public AbstractAlgorithm
{
    Q_OBJECT
public:
    BfsAlgorithm(QMutex *mtx, Graph *graph, bool &isExit,QWaitCondition *condit);
protected:
    void updateBfs(QVector<QVector<int> > Matrix, QVector<bool> Visited, QVector<int> Stack);
    void runBfs(int startEdge);

public slots:
    void runAlgo();

signals:

private:

};
#endif // BFSALGORITHM_H
