#include "mazegeneratorthread.h"

MazeGeneratorThread::MazeGeneratorThread(QPixmap &pathPixmap, QImage &resultImage, qreal distance, int error,
                                         QGraphicsItem *item, QPointF &startingPos, QPointF &terminalPos,
                                         const int *dx, const int *dy)
    : pathPixmap(pathPixmap), resultImage(resultImage), distance(distance), error(error),
      item(item), startingPos(startingPos), terminalPos(terminalPos), dx(dx), dy(dy)
{

}

void MazeGeneratorThread::run()
{
    int height = pathPixmap.height();
    int width = pathPixmap.width();
    QImage pathImage = pathPixmap.toImage();
    resultImage = QImage(pathPixmap.size(), QImage::Format_RGB888);
    resultImage.fill(Qt::white);
    std::priority_queue<std::pair<std::pair<qreal, int>, std::pair<std::pair<int, int>, std::pair<int, int> > > > pq;
    std::vector<std::vector<bool> > wall(height);
    auto isValid = [height, width](int x, int y)
    {
        return x >= 0 && x < height && y >= 0 && y < width;
    };
    int wallCnt = width * height / distance;
    int interval = wallCnt / 500;
    int counter = 0;
    for (int i = 0; i < height; ++i)
    {
        wall[i].resize(width, 0);
        for (int j = 0; j < width; ++j)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                wall[i][j] = true;
                resultImage.setPixel(j, i, qRgb(0, 0, 0));
                for (int k = 0; k < 4; ++k)
                {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (isValid(nx, ny) && !(nx == 0 || nx == height - 1 || ny == 0 || ny == width - 1))
                    {
                        pq.push(std::make_pair(std::make_pair(rand(), width * height),
                                               std::make_pair(std::make_pair(nx, ny), std::make_pair(i, j))));
                    }
                }
            }
        }
    }
    while (!pq.empty())
    {
        int x = pq.top().second.first.first;
        int y = pq.top().second.first.second;
        int lx = pq.top().second.second.first;
        int ly = pq.top().second.second.second;
        int s = pq.top().first.second;
        pq.pop();
        if (qAlpha(pathImage.pixel(y, x)))
        {
            s = qMin(s, error);
        }
        if (wall[x][y] || s <= 0 ||
                (startingPos.x() != -1 &&
                 (startingPos.x() - y) * (startingPos.x() - y)
                 + (startingPos.y() - x) * (startingPos.y() - x) <= 100) ||
                (terminalPos.x() != -1 &&
                 (terminalPos.x() - y) * (terminalPos.x() - y)
                 + (terminalPos.y() - x) * (terminalPos.y() - x) <= 100))
            continue;
        bool flag = true;
        for (int i = qMax(x - distance, 0.0); i <= qMin(x + distance, height - 1.0) && flag; ++i)
        {
            for (int j = qMax(y - distance, 0.0); j <= qMin(y + distance, width - 1.0) && flag; ++j)
            {
                if (wall[i][j] && qMin(hypot(i - x, j - y), distance) < qMin(hypot(i - lx, j - ly), distance))
                {
                    flag = false;
                }
            }
        }
        if (!flag)
            continue;
        wall[x][y] = true;
        resultImage.setPixel(y, x, qRgb(0, 0, 0));
        if (counter++ == interval)
        {
            item->update();
            item->setFocus();
            qApp->processEvents();
            counter = 0;
        }
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny) && !wall[nx][ny])
            {
                pq.push(std::make_pair(std::make_pair(rand(), s - 1),
                                       std::make_pair(std::make_pair(nx, ny), std::make_pair(x, y))));
            }
        }
    }
}
