#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QStack>
#include <SceneElements/graph.h>
#include <QMutexLocker>

class AbstractAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit AbstractAlgorithm(QMutex *mtx, Graph *graph, bool &isExit,QWaitCondition *condit);
    void setStartEdge(int edge);

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

public slots:
    virtual void runAlgo()=0;

protected:
    void lockLine(int codeLineIndex);

    QWaitCondition *_condit;
    QMutex *_mtx;
    const Graph _graph;
    bool & _isExit;
    int _startEdge;
};

#endif // ABSTRACTALGORITHM_H
