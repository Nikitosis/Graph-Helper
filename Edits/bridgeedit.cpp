#include "bridgeedit.h"
#include "ui_bridgeedit.h"

BridgeEdit::BridgeEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BridgeEdit)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void BridgeEdit::setBridge(Bridge *bridge)
{
    _bridge=bridge;
    ui->BridgeWeight->setText(QString::number(bridge->getWeight()));
}


BridgeEdit::~BridgeEdit()
{
    delete ui;
}

void BridgeEdit::on_BridgeWeight_textChanged(const QString &arg1)
{
    _bridge->setWeight(arg1.toInt());
}
