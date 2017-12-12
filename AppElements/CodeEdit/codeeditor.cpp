#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent):QPlainTextEdit(parent)
{
    lineNumberArea=new LineNumberArea(this);

    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberAreaWidth(int)));
    connect(this,SIGNAL(updateRequest(QRect,int)),this,SLOT(updateLineNumberArea(QRect,int)));

    updateLineNumberAreaWidth(0);

}
