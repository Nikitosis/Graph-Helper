#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "AppElements/CodeEdit/codeeditor.h"

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    explicit LineNumberArea(CodeEditor *editor);

    QSize sizeHint() const override;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
private:
    CodeEditor *_codeEditor;
};

#endif // LINENUMBERAREA_H
