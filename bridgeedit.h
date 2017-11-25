#ifndef BRIDGEEDIT_H
#define BRIDGEEDIT_H

#include <QWidget>
#include "bridge.h"

namespace Ui {
class BridgeEdit;
}

class BridgeEdit : public QWidget
{
    Q_OBJECT

public:
    explicit BridgeEdit(QWidget *parent = 0);

    void setBridge(Bridge *bridge);
    ~BridgeEdit();

private slots:
    void on_BridgeWeight_textChanged(const QString &arg1);

private:
    Bridge *_bridge;
    Ui::BridgeEdit *ui;
};

#endif // BRIDGEEDIT_H
