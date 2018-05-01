#include "abstractalgorithm.h"

AbstractAlgorithm::AbstractAlgorithm(QMutex *mtx, Graph *graph, bool &isExit, QWaitCondition *condit):
_mtx(mtx),
_graph(graph),
_isExit(isExit),
_condit(condit)
{

}

void AbstractAlgorithm::setStartEdge(int edge)
{
    _startEdge=edge;
}

void AbstractAlgorithm::lockLine(int codeLineIndex)
{
    qDebug()<<_isExit;
    if(_isExit)
        return;
    emit updateEditor(codeLineIndex);
    emit handleSignals();
    _condit->wait(_mtx);
}
