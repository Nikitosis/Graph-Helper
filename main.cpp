#include <Forms/mainwindow.h>
#include <QApplication>
#include <QItemSelection>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qRegisterMetaType<QItemSelection>("QItemSelection");
    qRegisterMetaType<QVector<int> >("QVector<int>");
    qRegisterMetaType<QVector<QVector<int> > >("QVector<QVector<int> >");
    qRegisterMetaType<QVector<bool> >("QVector<bool>");
    qRegisterMetaType<QVector<QVector<QString> > >("QVector<QVector<QString> >");
    qRegisterMetaType<QVector<QString>>("QVector<QString>");

    return a.exec();
}
