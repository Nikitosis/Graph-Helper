#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QObject>
#include <QPlainTextEdit>
#include <QPainter>
#include <QFontMetrics>
#include <QTextBlock>
#include <QPaintEvent>
//#include "AppElements/CodeEdit/linenumberarea.h"

class CodeEditor:public QPlainTextEdit
{
    Q_OBJECT
public:

    CodeEditor(QWidget *parent=0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void enableDebugMode(int blockIndex);
    void disableDebugMode();

protected:
    void resizeEvent(QResizeEvent *e);
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect& rect,int scrolly);
private:
    QWidget *_lineNumberArea;
    QPixmap _pixMap;
    int _debugBlockIndex;
};

#endif // CODEEDITOR_H
