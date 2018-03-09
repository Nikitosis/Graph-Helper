#ifndef VISUALARRAY_H
#define VISUALARRAY_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QVBoxLayout>

namespace Ui {
class VisualArray;
}

class VisualArray : public QWidget
{
    Q_OBJECT

public:
    explicit VisualArray(QWidget *parent = 0);
    explicit VisualArray(QVector<QString> value,QWidget *parent = 0);
    void init(QVector<QString> values);
    ~VisualArray();

private:
    Ui::VisualArray *ui;
};

#endif // VISUALARRAY_H
