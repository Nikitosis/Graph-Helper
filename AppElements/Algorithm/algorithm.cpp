#include "algorithm.h"

Algorithm::Algorithm(QMutex *mtx, Graph* graph, bool *isExit):_mtx(mtx),_graph(graph),_isExit(isExit)
{
}

Algorithm::Algorithm()
{

}

void Algorithm::runDFS(int startEdge)
{
    _mtx->lock();

    QVector<QVector<int>> &Matrix=_graph.getCorrectMatrix();
    QVector<MyEdge *> Edges=_graph.getEdges();
    QVector<bool> Visited(Matrix.size());
    QVector<int> Stack;
    QVector<QPair<int,int>> BridgesVec;

    if(Matrix.size()==0)
    {
        *_isExit=true;
        _mtx->unlock();
        return;
    }

   emit updateDfs(Matrix,Visited,Stack);
   emit lockLine(4);

    Visited[startEdge]=true;

   emit updateDfs(Matrix,Visited,Stack);
   emit lockLine(5);

    Stack.push_back(startEdge);

    emit updateDfs(Matrix,Visited,Stack);
    emit lockLine(6);

    while(!Stack.empty())
    {
        emit changeEdgeColor(Edges[Stack.last()]->getId(),ACTIVE_BRIDGE_COLOR);
        emit updateDfs(Matrix,Visited,Stack);
        emit lockLine(8);
        for(int i=0;i<Matrix.size();i++)
        {
            emit lockLine(9);
            emit lockLine(10);
            if(Matrix[Stack.last()][i]!=0 && !Visited[i])
            {
                emit changeBridgeColor(Edges[Stack.last()]->getId(),Edges[i]->getId(),ACTIVE_BRIDGE_COLOR);
                emit changeEdgeColor(Edges[i]->getId(),ACTIVE_BRIDGE_COLOR);
                emit changeEdgeColor(Edges[Stack.last()]->getId(),PASSIVE_BRIDGE_COLOR);
                if(BridgesVec.size()>0)
                {
                    int first=BridgesVec[BridgesVec.size()-1].first;
                    int second=BridgesVec[BridgesVec.size()-1].second;
                    emit changeBridgeColor(Edges[first]->getId(),Edges[second]->getId(),PASSIVE_BRIDGE_COLOR);
                }
                BridgesVec.push_back({Stack.last(),i});

                emit lockLine(11);
                emit lockLine(12);

                Visited[i]=true;

                emit updateDfs(Matrix,Visited,Stack);
                emit lockLine(13);

                Stack.push_back(i);

                emit updateDfs(Matrix,Visited,Stack);
                emit lockLine(14);

                i=-1;

                emit updateDfs(Matrix,Visited,Stack);
                emit lockLine(15);
            }
            emit lockLine(16);
        }
        emit changeEdgeColor(Edges[Stack.last()]->getId(),PASSIVE_BRIDGE_COLOR);
        if(BridgesVec.size()>0)
        {
            int first=BridgesVec[BridgesVec.size()-1].first;
            int second=BridgesVec[BridgesVec.size()-1].second;
            emit changeBridgeColor(Edges[first]->getId(),Edges[second]->getId(),PASSIVE_BRIDGE_COLOR);
            BridgesVec.pop_back();
        }

        emit updateDfs(Matrix,Visited,Stack);
        emit lockLine(17);

        Stack.pop_back();

        emit updateDfs(Matrix,Visited,Stack);
        emit lockLine(18);
    }

    emit updateDfs(Matrix,Visited,Stack);
    emit lockLine(19);
    qDebug()<<"Go!";

    _mtx->unlock();
    *_isExit=true;
}

void Algorithm::setStartEdge(int edge)
{
    QMutexLocker locker(_mtx);
    _startEdge=edge;
}

void Algorithm::runAlgo()
{
    qDebug()<<"Thread running"<<QThread::currentThreadId();
    runDFS(_startEdge);
}


