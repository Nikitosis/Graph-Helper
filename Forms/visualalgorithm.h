#ifndef VISUALALGORITHM_H
#define VISUALALGORITHM_H

#include <QDialog>
#include <QSize>
#include <QString>
#include <QVector>
#include <QTreeWidget>
#include <QVector>
#include <QStack>
//////
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
//////
#include <Forms/visualarray.h>
#include <SceneElements/graph.h>
#include <AppElements/visualalgorithmsceneview.h>

namespace Ui {
class VisualAlgorithm;
}

class VisualAlgorithm : public QDialog
{
    Q_OBJECT

public:
    explicit VisualAlgorithm(Graph *graph, QWidget *parent = 0);
    void init();
    ~VisualAlgorithm();
protected:
    void addOneDArray(QVector<QString> &values, QVector<QString> &names, QString mainName);
    void addTwoDArray(QVector<QVector<QString> > &values, QVector<QString> &arrayNames, QVector<QString> valueNames, QString mainName);
    void initCodeText();
    void changeBridgeColor(int startEdgeId, int endEdgeId,QColor color);
    void changeEdgeColor(int id,QColor color);
    void changeAllBridgesColor(QColor color);
    void changeAllEdgesColor(QColor color);

    void DFS();
    void initDFS();
    void updateDFS(QVector<QVector<int>> &Matrix, QVector<bool> &Visited, QVector<int> &Stack);
    void LockLine(int codeLineIndex);
signals:

protected slots:


private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void reject();

private:
    Graph *_graph;
    Ui::VisualAlgorithm *ui;
    QMutex mtx;
    QWaitCondition condit;
    QFuture<void> future;
    bool isExit;
};

#endif // VISUALALGORITHM_H
