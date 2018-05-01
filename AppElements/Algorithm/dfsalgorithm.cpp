#include "dfsalgorithm.h"


DfsAlgorithm::DfsAlgorithm(QMutex *mtx, Graph* graph, bool &isExit, QWaitCondition *condit):AbstractAlgorithm(mtx,graph,isExit,condit)
{
}


void DfsAlgorithm::runDfs(int startEdge)
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

   updateDfs(Matrix,Visited,Stack);
   lockLine(4);

   Visited[startEdge]=true;

   updateDfs(Matrix,Visited,Stack);
   lockLine(5);

    Stack.push_back(startEdge);

    updateDfs(Matrix,Visited,Stack);
    lockLine(6);

    while(!Stack.empty())
    {
        emit changeEdgeColor(Edges[Stack.last()]->getId(),ACTIVE_BRIDGE_COLOR);
        emit updateDfs(Matrix,Visited,Stack);
        lockLine(8);
        for(int i=0;i<Matrix.size();i++)
        {
            lockLine(9);
            lockLine(10);
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

                lockLine(11);
                lockLine(12);

                Visited[i]=true;

                updateDfs(Matrix,Visited,Stack);
                lockLine(13);

                Stack.push_back(i);

                updateDfs(Matrix,Visited,Stack);
                lockLine(14);

                i=-1;

                updateDfs(Matrix,Visited,Stack);
                lockLine(15);
            }
            lockLine(16);
        }
        emit changeEdgeColor(Edges[Stack.last()]->getId(),PASSIVE_BRIDGE_COLOR);
        if(BridgesVec.size()>0)
        {
            int first=BridgesVec[BridgesVec.size()-1].first;
            int second=BridgesVec[BridgesVec.size()-1].second;
            emit changeBridgeColor(Edges[first]->getId(),Edges[second]->getId(),PASSIVE_BRIDGE_COLOR);
            BridgesVec.pop_back();
        }

        updateDfs(Matrix,Visited,Stack);
        lockLine(17);

        Stack.pop_back();

        updateDfs(Matrix,Visited,Stack);
        lockLine(18);
    }

    updateDfs(Matrix,Visited,Stack);
    lockLine(19);
    qDebug()<<"Go!";

    _mtx->unlock();
    _isExit=true;
}

void DfsAlgorithm::updateDfs(QVector<QVector<int> > Matrix, QVector<bool> Visited, QVector<int> Stack)
{
    qDebug()<<"UPDATE THREAT"<<QThread::currentThreadId();
    if(_isExit)
        return;

    emit watchSaveState();
    emit watchClear();

    QVector<MyEdge *>Edges=_graph.getEdges();
    QVector<QString> Names(Edges.size());
    QVector<QVector<QString>> StringMatrix(Matrix.size());

    for(int i=0;i<Edges.size();i++)
    {
        QString k=Edges[i]->getInfo();
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

    emit watchAddOneDArray(StackNames,Numbers,"Stack");

    emit watchResetState();
    emit handleSignals();
}

void DfsAlgorithm::runAlgo()
{
    qDebug()<<"Thread running"<<QThread::currentThreadId();
    runDfs(_startEdge);
}
