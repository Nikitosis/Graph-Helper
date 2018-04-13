#include "codeeditor.h"
#include "linenumberarea.h"

CodeEditor::CodeEditor(QWidget *parent):QPlainTextEdit(parent)
{
    _lineNumberArea=new LineNumberArea(this);

    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberAreaWidth(int)));
    connect(this,SIGNAL(updateRequest(QRect,int)),this,SLOT(updateLineNumberArea(QRect,int)));

    updateLineNumberAreaWidth(0);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    _pixMap.load(":/Debug/img/DebugArrow.png");
    _debugBlockIndex=-1;
    _prevDebugBlockIndex=-1;
    setReadOnly(true);
    setUndoRedoEnabled(false);
}

CodeEditor::~CodeEditor()
{
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    qDebug()<<"Paint"<<endl;
    QPainter painter(_lineNumberArea);
    painter.fillRect(event->rect(),Qt::lightGray);

    QTextBlock block=firstVisibleBlock();
    int blockNumber=block.blockNumber();
    int top=(int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom=top+(int)blockBoundingGeometry(block).height();
    QTextBlockFormat fm;
    fm.setBackground(QColor(201,225,226));

    while(block.isValid() && top<=event->rect().bottom())
    {
        if(block.isVisible() && bottom>=event->rect().top())
        {
            QString number=QString::number(blockNumber+1);
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial",10));
            painter.drawText(QRect(0,top,lineNumberAreaWidth(),fontMetrics().height()),Qt::AlignRight,number);
            if(blockNumber==_debugBlockIndex)
            {
                //painter.drawPixmap(QRect(0,top,15,fontMetrics().height()),_pixMap);
            }
        }

        block=block.next();
        top=bottom;
        bottom=top+(int) blockBoundingGeometry(block).height();
        blockNumber++;
    }
    if(_prevDebugBlockIndex!=-1 && _prevDebugBlockIndex!=_debugBlockIndex)//clear previous colored block
    {
        QTextDocument *document=this->document();

        fm.setBackground(Qt::white);
        QTextCursor(document->findBlockByNumber(_prevDebugBlockIndex)).setBlockFormat(fm);
    }
    if(_prevDebugBlockIndex!=_debugBlockIndex) //paint current block
    {
        QTextDocument *document=this->document();

        QTextBlock curBlock=document->findBlockByNumber(_debugBlockIndex);

        fm.setBackground(QColor(201,225,226));
        QTextCursor(curBlock).setBlockFormat(fm);
    }

    if(_debugBlockIndex!=-1)
    {
        QTextDocument *document=this->document();
        QTextBlock curBlock=document->findBlockByNumber(_debugBlockIndex);
        int curTop=(int)blockBoundingGeometry(curBlock).translated(contentOffset()).top();
        painter.drawPixmap(QRect(0,curTop,15,fontMetrics().height()),_pixMap);
    }

    _prevDebugBlockIndex=_debugBlockIndex;

    qDebug()<<"End"<<endl;


}

int CodeEditor::lineNumberAreaWidth()
{
    int digits=1;
    int maxLines=qMax(1,blockCount());
    while(maxLines>=10)
    {
        maxLines/=10;
        digits++;
    }
    return 15+fontMetrics().width('9')*digits;
}

void CodeEditor::enableDebugMode(int blockIndex)
{
    _debugBlockIndex=blockIndex;
}

void CodeEditor::disableDebugMode()
{
    _debugBlockIndex=-1;
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr=contentsRect();
    _lineNumberArea->setGeometry(QRect(cr.left(),cr.top(),lineNumberAreaWidth(),cr.height()));
}

void CodeEditor::updateLineNumberAreaWidth(int newBlockCount)
{
    setViewportMargins(lineNumberAreaWidth(),0,0,0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int scrolly)
{
    if(scrolly)
        _lineNumberArea->scroll(0,scrolly);
    else
        _lineNumberArea->update(0,rect.y(),lineNumberAreaWidth(),rect.height());

    if(rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}
