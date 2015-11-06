#ifndef MYVIEW_H
#define MYVIEW_H

#include <QWidget>
#include <QtWidgets>
#include "mazewidget.h"

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(QGraphicsScene *scene);

public slots:
    void setDrawStatus(MazeWidget::DrawStatus status);

private:
    bool space;
    bool mousePress;
    MazeWidget::DrawStatus status;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MYVIEW_H
