#ifndef VISUALALGORITHM_H
#define VISUALALGORITHM_H

#include <QDialog>
#include <QSize>
#include <QString>
#include <QVector>
#include <QTreeWidget>
#include <QVector>
#include <Forms/visualarray.h>
//////
#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
//////
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
    void addTwoDArray(QVector<QVector<QString> > &values, QVector<QString> &arrayNames, QVector<QVector<QString> > valueNames, QString mainName);
    void initCodeText();
    void changeBridgeColor(int id);
    void changeEdgeColor(int id);

    void Algo();
private slots:

    void on_pushButton_clicked();

private:
    Graph *_graph;
    Ui::VisualAlgorithm *ui;
    QMutex mtx;
    QWaitCondition condit;
};

#endif // VISUALALGORITHM_H
