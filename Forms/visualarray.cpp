#include "visualarray.h"
#include "ui_visualarray.h"

VisualArray::VisualArray(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualArray)
{
    ui->setupUi(this);
}

VisualArray::VisualArray(QVector<QString> value, QWidget *parent):
    QWidget(parent),
    ui(new Ui::VisualArray)
{
     ui->setupUi(this);
     init(value);
}

void VisualArray::init(QVector<QString> values)
{
    int maxWidth=ui->Name->text().length()*ui->Name->font().pointSize();
    for(int i=0;i<values.size();i++)
    {
        QVBoxLayout *layout=new QVBoxLayout();
        QLabel *value=new QLabel(values[i]);
        QLabel *index=new QLabel(QString::number(i));


        value->setAlignment(Qt::AlignCenter);
        index->setAlignment(Qt::AlignCenter);
        layout->addWidget(value);
        layout->addWidget(index);
        ui->Values->addLayout(layout);
        if(value->text().length()*value->font().pointSize()>maxWidth)
            maxWidth=value->text().length()*value->font().pointSize();

        if(index->text().length()*index->font().pointSize()>maxWidth)
            maxWidth=index->text().length()*index->font().pointSize();
    }
    this->setFixedWidth(maxWidth*values.size()+maxWidth+5);

}


VisualArray::~VisualArray()
{
    delete ui;
}
