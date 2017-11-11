#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

#include <QDialog>
#include <QVector>

namespace Ui {
class VisualGraph;
}

class VisualGraph : public QDialog
{
    Q_OBJECT

public:
    explicit VisualGraph(QWidget *parent = 0);
    ~VisualGraph();
    void init(QVector<QVector<int>> Vec);

private:
    Ui::VisualGraph *ui;
};

#endif // VISUALGRAPH_H
