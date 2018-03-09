#include "edgeedit.h"
#include "ui_edgeedit.h"

EdgeEdit::EdgeEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdgeEdit)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
}

void EdgeEdit::setEdge(MyEdge *edge)
{
    _edge=edge;
    ui->edgeName->setText(_edge->getInfo());
}

EdgeEdit::~EdgeEdit()
{
    delete ui;
}

void EdgeEdit::on_edgeName_textChanged(const QString &arg1)
{
    _edge->setInfo(arg1);
}
