#ifndef VISUALALGORITHMSCENEVIEW_H
#define VISUALALGORITHMSCENEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScrollBar>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <SceneElements/myedge.h>

class VisualAlgorithmSceneView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit VisualAlgorithmSceneView(QWidget *parent = nullptr);
    void addElement(QGraphicsItem *element);
    QGraphicsScene *getScene() const;

signals:

public slots:
    void wheelEvent(QWheelEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressMiddleButton(QMouseEvent *event);
    void mouseMoveMiddleButton(QMouseEvent *event);

private:
    QGraphicsScene *scene;
    int originPosX;
    int originPosY;

    QTimer *timer; //update optimization

};

#endif // VISUALALGORITHMSCENEVIEW_H
