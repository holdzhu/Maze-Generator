#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <vector>
#include <queue>

class MazeWidget : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum DrawStatus
    {
        ARROW,
        BRUSH,
        ERASER,
        STARTING,
        TERMINAL
    };
    MazeWidget();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void resize(int width, int height);
    QSize size() const;
    void save();

signals:

public slots:
    void setDrawStatus(MazeWidget::DrawStatus status);
    void setPathVisibility(bool pathVisibility);
    void clear();
    void generate();
    void setDistance(int distance);
    void setError(int error);

    // QWidget interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    static const int dx[];
    static const int dy[];
    QPixmap pathPixmap;
    QImage resultImage;
    DrawStatus status;
    bool isMouseDown;
    bool showResult;
    QPointF lastPos;
    QPointF startingPos;
    QPointF terminalPos;
    QSize _size;
    qreal distance;
    int error;
    bool pathVisibility;

    // QGraphicsItem interface
protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // MAZEWIDGET_H
