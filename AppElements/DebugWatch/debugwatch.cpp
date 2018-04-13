#include "debugwatch.h"

DebugWatch::DebugWatch(QWidget *parent):QTreeWidget(parent)
{

}

void DebugWatch::addOneDArray(QVector<QString> &values, QVector<QString> &names, QString mainName)
{
    QTreeWidgetItem *mainItem=new QTreeWidgetItem(this);
    mainItem->setText(0,mainName);
    for(int i=0;i<names.size();i++)
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
