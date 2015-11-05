#ifndef MYVIEW_H
#define MYVIEW_H

#include <QWidget>
#include <QtWidgets>

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(QGraphicsScene *scene);

private:
    bool space;
    bool mousePress;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MYVIEW_H
