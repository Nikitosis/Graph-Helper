#ifndef DEBUGWATCH_H
#define DEBUGWATCH_H

#include <QTreeWidget>
#include <QObject>


class DebugWatch : public QTreeWidget
{
public:
    DebugWatch(QWidget *parent=nullptr);

    void addOneDArray(QVector<QString> &values, QVector<QString> &names, QString mainName);
    void addTwoDArray(QVector<QVector<QString> > &values, QVector<QString> &arrayNames, QVector<QString> &valueNames, QString mainName);
};

#endif // DEBUGWATCH_H
