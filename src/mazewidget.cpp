#include "mazewidget.h"

const int MazeWidget::dx[] = {0, 0, 1, -1};
const int MazeWidget::dy[] = {1, -1, 0, 0};

MazeWidget::MazeWidget() : QGraphicsItem(), status(ARROW), isMouseDown(false), showResult(false), pathVisibility(false)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void MazeWidget::setDrawStatus(MazeWidget::DrawStatus status)
{
    this->status = status;
}

void MazeWidget::setPathVisibility(bool pathVisibility)
{
    this->pathVisibility = pathVisibility;
    update();
}

void MazeWidget::clear()
{
    pathPixmap.fill(Qt::transparent);
    startingPos = QPoint(-1, -1);
    terminalPos = QPoint(-1, -1);
    showResult = false;
    update();
}

void MazeWidget::generate(qreal distance, int error)
{
    showResult = true;
    MazeGeneratorThread *thread = new MazeGeneratorThread(pathPixmap, resultImage, distance, error, this,
                                                          startingPos, terminalPos, dx, dy);
    thread->run();
}

void MazeWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    isMouseDown = true;
    lastPos = event->pos();
    if (status == STARTING)
    {
        showResult = false;
        startingPos = event->pos();
    }
    else if (status == TERMINAL)
    {
        showResult = false;
        terminalPos = event->pos();
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MazeWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    isMouseDown = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void MazeWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (isMouseDown)
    {
        QPainter painter(&pathPixmap);
        if (status == BRUSH)
        {
            showResult = false;
            painter.setBrush(Qt::red);
            painter.setPen(Qt::red);
            painter.drawLine(lastPos, event->pos());
            lastPos = event->pos();
            update();
        }
        else if (status == ERASER)
        {
            showResult = false;
            painter.setCompositionMode(QPainter::CompositionMode_Clear);
            QPen pen(Qt::transparent);
            pen.setWidth(20);
            painter.setPen(pen);
            painter.drawLine(lastPos, event->pos());
        }
        else if (status == STARTING)
        {
            showResult = false;
            startingPos = event->pos();
        }
        else if (status == TERMINAL)
        {
            showResult = false;
            terminalPos = event->pos();
        }
        lastPos = event->pos();
        update();
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void MazeWidget::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}

QRectF MazeWidget::boundingRect() const
{
    return QRectF(QPoint(0, 0), size());
}

void MazeWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawRect(boundingRect());
    if (showResult)
    {
        painter->drawImage(0, 0, resultImage);
    }
    if (pathVisibility || !showResult)
    {
        painter->drawPixmap(0, 0, pathPixmap);
    }
    QFont font = painter->font();
    font.setPointSize(font.pointSize() * 2);
    painter->setFont(font);
    if (startingPos.x() != -1)
    {
        painter->setPen(Qt::blue);
        painter->drawText(QRect(startingPos.x() - 10, startingPos.y() - 10, 20, 20), Qt::AlignCenter, tr("S"));
    }
    if (terminalPos.x() != -1)
    {
        painter->setPen(Qt::blue);
        painter->drawText(QRect(terminalPos.x() - 10, terminalPos.y() - 10, 20, 20), Qt::AlignCenter, tr("T"));
    }
}

void MazeWidget::resize(int width, int height)
{
    _size = QSize(width, height);
    pathPixmap = QPixmap(size());
    clear();
    scene()->setSceneRect(boundingRect());
    scene()->update();
}

QSize MazeWidget::size() const
{
    return _size;
}

void MazeWidget::save()
{
    QImage image(boundingRect().size().toSize(), QImage::Format_RGB32);
    image.fill(QColor(0, 0, 0).rgb());
    QPainter painter(&image);
    QStyleOptionGraphicsItem styleOption;
    paint(&painter, &styleOption, NULL);
    painter.end();
    QString path = QFileDialog::getSaveFileName(NULL, tr("Save Image"), tr(""), tr("Image(*.png)"));
    image.save(path);
}


