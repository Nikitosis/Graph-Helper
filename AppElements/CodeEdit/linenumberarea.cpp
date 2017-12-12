#include "linenumberarea.h"

LineNumberArea::LineNumberArea(CodeEditor *parent) : QWidget(parent)
{
    codeEditor=parent;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(codeEditor->lineNumberAreaWith,0);
}
