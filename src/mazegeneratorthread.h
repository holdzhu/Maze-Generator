#ifndef MAZEGENERATORTHREAD_H
#define MAZEGENERATORTHREAD_H

#include <QtWidgets>
#include <queue>
#include <vector>

class MazeGeneratorThread : public QThread
{
    Q_OBJECT
public:
    MazeGeneratorThread(QPixmap &pathPixmap, QImage &resultImage, qreal distance, int error,
                        QGraphicsItem *item, QPointF &startingPos, QPointF &terminalPos,
                        const int *dx, const int *dy);
    void run();

private:
    QPixmap &pathPixmap;
    QImage &resultImage;
    qreal distance;
    int error;
    QGraphicsItem *item;
    QPointF &startingPos;
    QPointF &terminalPos;
    const int *dx;
    const int *dy;
};

#endif // MAZEGENERATORTHREAD_H
