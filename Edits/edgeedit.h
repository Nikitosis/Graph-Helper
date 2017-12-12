#ifndef EDGEEDIT_H
#define EDGEEDIT_H

#include <QWidget>
#include <QDialog>
#include <QGraphicsItem>
#include "SceneElements/myedge.h"


namespace Ui {
class EdgeEdit;
}

class EdgeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit EdgeEdit(QWidget *parent = 0);

    void setEdge(MyEdge *edge);
    ~EdgeEdit();

private slots:
    void on_edgeName_textChanged(const QString &arg1);

private:
    MyEdge *_edge;
    Ui::EdgeEdit *ui;
};

#endif // EDGEEDIT_H
