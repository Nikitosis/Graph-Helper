#ifndef VISUALALGORITHM_H
#define VISUALALGORITHM_H

#include <QDialog>
#include <QSize>
#include <QString>
#include <QVector>
#include <QTreeWidget>
#include <Forms/visualarray.h>

namespace Ui {
class VisualAlgorithm;
}

class VisualAlgorithm : public QDialog
{
    Q_OBJECT

public:
    explicit VisualAlgorithm(QWidget *parent = 0);
    void init();
    ~VisualAlgorithm();
protected:
    void addOneDArray(QVector<QString> &values, QVector<QString> &names, QString mainName);
    void addTwoDArray(QVector<QVector<QString> > &values, QVector<QString> &arrayNames, QVector<QVector<QString> > valueNames, QString mainName);
    void initCodeText();
private:
    Ui::VisualAlgorithm *ui;
};

#endif // VISUALALGORITHM_H
