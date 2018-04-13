#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

#include <QDialog>
#include <QVector>
#include <QString>
#include <QScrollBar>
#include <QtAlgorithms>
#include <algorithm>
#include "SceneElements/myedge.h"

namespace Ui {
class VisualGraph;
}

class VisualGraph : public QDialog
{
    Q_OBJECT

public:
    explicit VisualGraph(QWidget *parent = 0);
    ~VisualGraph();
    void init(QVector<QVector<int>> Vec,QVector<MyEdge*> Edges);
    void initMatrix(const QVector<QVector<int> > &Vec, const QVector<MyEdge *> &Edges);
    void initList(const QVector<QVector<int> > &Vec, const QVector<MyEdge *> &Edges);
    void initBridge(const QVector<QVector<int> > &Vec, const QVector<MyEdge *> &Edges);
    void initIncidence(const QVector<QVector<int> > &Vec, const QVector<MyEdge *> &Edges);
    void initHelp();

private:
    Ui::VisualGraph *ui;
};

#endif // VISUALGRAPH_H
