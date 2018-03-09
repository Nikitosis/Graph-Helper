#include "linenumberarea.h"

LineNumberArea::LineNumberArea(CodeEditor *editor) : QWidget(editor)
{
    _codeEditor=editor;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(_codeEditor->lineNumberAreaWidth(),0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    _codeEditor->lineNumberAreaPaintEvent(event);
}
