#include "bfsalgorithm.h"

BfsAlgorithm::BfsAlgorithm(QMutex *mtx, Graph *graph, bool &isExit, QWaitCondition *condit):AbstractAlgorithm(mtx,graph,isExit,condit)
{

}

void BfsAlgorithm::updateBfs(QVector<QVector<int> > Matrix, QVector<bool> Visited, QVector<int> Stack)
{
    if(_isExit)
        return;

    emit watchSaveState();
    emit watchClear();

    QVector<MyEdge *>Edges=_graph.getEdges();
    QVector<QString> Names(Edges.size());
    QVector<QVector<QString>> StringMatrix(Matrix.size());

    for(int i=0;i<Edges.size();i++)
    {
        Names[i]=Edges[i]->getInfo();
    }

    for(int i=0;i<Matrix.size();i++)
        for(int j=0;j<Matrix[i].size();j++)
            StringMatrix[i].push_back(QString::number(Matrix[i][j]));


    emit watchAddTwoDArray(StringMatrix,Names,Names,"Matrix");
    emit handleSignals();

    QVector<QString> Values;
    for(int i=0;i<Visited.size();i++)
        Values.push_back(QString::number(Visited[i]));

    emit watchAddOneDArray(Values,Names,"Visited");
    emit handleSignals();


    QVector<QString> StackNames;
    for(int i=0;i<Stack.size();i++)
        StackNames.push_back(Edges[Stack[i]]->getInfo());
    QVector<QString> Numbers;
    for(int i=0;i<Stack.size();i++)
        Numbers.push_back(QString::number(i+1));

    emit watchAddOneDArray(StackNames,Numbers,"Queue");

    emit watchResetState();
    emit handleSignals();
}

void BfsAlgorithm::runBfs(int startEdge)
{
    _mtx->lock();

    QVector<QVector<int>> &Matrix=_graph.getCorrectMatrix();
    QVector<MyEdge *> Edges=_graph.getEdges();
    QVector<bool> Visited(Matrix.size());
    QVector<int> Stack;
    QVector<QPair<int,int>> BridgesVec;

    if(Matrix.size()==0)
    {
        _isExit=true;
        _mtx->unlock();
        return;
    }

   updateBfs(Matrix,Visited,Stack);
   lockLine(4);

   Visited[startEdge]=true;

   updateBfs(Matrix,Visited,Stack);
   lockLine(5);

   Stack.push_back(startEdge);

   updateBfs(Matrix,Visited,Stack);
   lockLine(6);

    while(!Stack.empty())
    {
        emit changeEdgeColor(Edges[Stack.first()]->getId(),ACTIVE_BRIDGE_COLOR);
        emit updateBfs(Matrix,Visited,Stack);
        lockLine(8);
        for(int i=0;i<Matrix.size();i++)
        {
            lockLine(9);
            lockLine(10);
            if(Matrix[Stack.first()][i]!=0 && !Visited[i])
            {
                emit changeBridgeColor(Edges[Stack.first()]->getId(),Edges[i]->getId(),ACTIVE_BRIDGE_COLOR);
                emit changeEdgeColor(Edges[i]->getId(),FUTURE_BRIDGE_COLOR);
                if(BridgesVec.size()>0)
                {
                    int first=BridgesVec[BridgesVec.size()-1].first;
                    int second=BridgesVec[BridgesVec.size()-1].second;
                    emit changeBridgeColor(Edges[first]->getId(),Edges[second]->getId(),PASSIVE_BRIDGE_COLOR);
                }
                BridgesVec.push_back({Stack.first(),i});

                lockLine(11);
                lockLine(12);

                Visited[i]=true;

                updateBfs(Matrix,Visited,Stack);
                lockLine(13);

                Stack.push_back(i);

                updateBfs(Matrix,Visited,Stack);
                lockLine(14);

            }
            lockLine(15);
        }
        emit changeEdgeColor(Edges[Stack.first()]->getId(),PASSIVE_BRIDGE_COLOR);
        if(BridgesVec.size()>0)
        {
            int first=BridgesVec[BridgesVec.size()-1].first;
            int second=BridgesVec[BridgesVec.size()-1].second;
            emit changeBridgeColor(Edges[first]->getId(),Edges[second]->getId(),PASSIVE_BRIDGE_COLOR);
            BridgesVec.pop_back();
        }

        updateBfs(Matrix,Visited,Stack);
        lockLine(16);

        Stack.pop_front();

        updateBfs(Matrix,Visited,Stack);
        lockLine(17);
    }

    updateBfs(Matrix,Visited,Stack);
    lockLine(18);
    qDebug()<<"Go!";

    _mtx->unlock();
    _isExit=true;
}

void BfsAlgorithm::runAlgo()
{
    qDebug()<<"Running BFS";
    runBfs(_startEdge);
}
