#ifndef VISUALALGORITHMSCENEVIEW_H
#define VISUALALGORITHMSCENEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScrollBar>
#include <SceneElements/myedge.h>

class VisualAlgorithmSceneView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit VisualAlgorithmSceneView(QWidget *parent = nullptr);
    void addElement(QGraphicsItem *element);

signals:

public slots:

private:
    QGraphicsScene *scene;

};

#endif // VISUALALGORITHMSCENEVIEW_H
