#include "myview.h"

MyView::MyView(QGraphicsScene *scene) : QGraphicsView(scene), space(false), mousePress(false),
    status(MazeWidget::ARROW)
{
    setMouseTracking(true);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setInteractive(false);
}

void MyView::setDrawStatus(MazeWidget::DrawStatus status)
{
    this->status = status;
    if (status == MazeWidget::ARROW)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
    }
    else
    {
        setDragMode(QGraphicsView::NoDrag);
        setInteractive(true);
    }
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    mousePress = true;
    if (space)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
        setInteractive(false);
    }
    QGraphicsView::mousePressEvent(event);
}

void MyView::mouseReleaseEvent(QMouseEvent *event)
{
    mousePress = false;
    if (space && status != MazeWidget::ARROW)
    {
        setDragMode(QGraphicsView::NoDrag);
        setInteractive(true);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void MyView::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
    {
        scale(1.1, 1.1);
    }
    else
    {
        scale(0.9, 0.9);
    }
}

void MyView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        space = true;
    }
    QGraphicsView::keyPressEvent(event);
}

void MyView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        space = false;
    }
    QGraphicsView::keyReleaseEvent(event);
}

