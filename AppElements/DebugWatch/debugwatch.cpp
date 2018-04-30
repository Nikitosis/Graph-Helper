#include "debugwatch.h"

DebugWatch::DebugWatch(QWidget *parent):QTreeWidget(parent)
{
}

void DebugWatch::addOneDArray(QVector<QString> &values, QVector<QString> &names, QString mainName)
{
    QTreeWidgetItem *mainItem=new QTreeWidgetItem(this);
    mainItem->setText(0,mainName);
    for(int i=0;i<names.size() && i<values.size();i++)
    {
        QTreeWidgetItem *item=new QTreeWidgetItem(mainItem);
        item->setText(0,names[i]);
        item->setText(1,values[i]);
    }
}

void DebugWatch::addTwoDArray(QVector<QVector<QString> > &values, QVector<QString> &arrayNames, QVector<QString> &valueNames, QString mainName)
{
    QTreeWidgetItem *mainItem=new QTreeWidgetItem(this);
    mainItem->setText(0,mainName);
    for(int i=0;i<arrayNames.size();i++)
    {
        QTreeWidgetItem *arrayItem=new QTreeWidgetItem(mainItem);
        arrayItem->setText(0,arrayNames[i]);

        for(int j=0;j<valueNames.size();j++)
        {
            QTreeWidgetItem *item=new QTreeWidgetItem(arrayItem);
            item->setText(0,valueNames[j]);
            item->setText(1,values[i][j]);
        }
    }
}

void DebugWatch::clearTabs()
{
    for(int i=0;i<this->topLevelItemCount();i++)
        delete this->topLevelItem(i);
}

QString DebugWatch::getHashTreeItem(QTreeWidgetItem *item)
{
    QString res="";
    while(item!=nullptr)
    {
        res+=item->text(0);
        item=item->parent();
    }
    return res;
}

void DebugWatch::saveState()
{
    qDebug()<<"DEBUG WATCH"<<QThread::currentThreadId();
    for(int i=0;i<this->topLevelItemCount();i++)
    {
        QString curHash=getHashTreeItem(this->topLevelItem(i));
        _hash.insert(curHash,this->topLevelItem(i)->isExpanded());
    }
}

void DebugWatch::resetState()
{
    for(int i=0;i<this->topLevelItemCount();i++)
    {
        QString curHash=getHashTreeItem(this->topLevelItem(i));
        this->topLevelItem(i)->setExpanded(_hash[curHash]);
    }
    _hash.clear();
}
