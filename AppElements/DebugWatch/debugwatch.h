#ifndef DEBUGWATCH_H
#define DEBUGWATCH_H

#include <QTreeWidget>
#include <QObject>
#include <QHash>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QThread>

class DebugWatch : public QTreeWidget
{
    Q_OBJECT
public:
    DebugWatch(QWidget *parent=nullptr);

public slots:
    void saveState();
    void resetState();
    void addOneDArray(QVector<QString> &values, QVector<QString> &names, QString mainName);
    void addTwoDArray(QVector<QVector<QString> > &values, QVector<QString> &arrayNames, QVector<QString> &valueNames, QString mainName);
    void clearTabs();
protected:
    QString getHashTreeItem(QTreeWidgetItem *item);
private:
    QHash<QString,bool> _hash;
};

#endif // DEBUGWATCH_H
