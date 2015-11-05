#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <mazewidget.h>
#include <myview.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

signals:
    void changeDrawStatus(MazeWidget::DrawStatus status);

private slots:
    void arrowActionTriggered();
    void brushActionTriggered();
    void eraserActionTriggered();
    void startingActionTriggered();
    void terminalActionTriggered();
    void resizeActionTriggered();
    void generateActionTriggered();
    void saveActionTriggered();
    void aboutActionTriggered();

private:
    QSlider *distanceSlider;
    QSlider *errorSlider;
    QLineEdit *widthEdit;
    QLineEdit *heightEdit;
    QCheckBox *showPathCheck;
    MazeWidget *mazeWidget;
    QGraphicsView *view;
};

#endif // MAINWINDOW_H
