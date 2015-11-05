#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *saveAction = new QAction(tr("Save"), fileMenu);
    saveAction->setToolTip(tr("Save"));
    saveAction->setStatusTip(tr("Save"));
    fileMenu->addAction(saveAction);
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAction = new QAction(tr("About"), helpMenu);
    aboutAction->setToolTip(tr("About"));
    aboutAction->setStatusTip(tr("About"));
    helpMenu->addAction(aboutAction);
    QToolBar *toolBar = this->addToolBar("Tools");
    QActionGroup *group = new QActionGroup(toolBar);
    QAction *arrowAction = new QAction(tr("Arrow"), toolBar);
    arrowAction->setIcon(QIcon(":/arrow.png"));
    arrowAction->setToolTip(tr("Arrow"));
    arrowAction->setStatusTip(tr("Arrow"));
    arrowAction->setCheckable(true);
    arrowAction->setChecked(true);
    toolBar->addAction(arrowAction);
    group->addAction(arrowAction);
    QAction *brushAction = new QAction(tr("Brush"), toolBar);
    brushAction->setIcon(QIcon(":/brush.png"));
    brushAction->setToolTip(tr("Brush"));
    brushAction->setStatusTip(tr("Brush"));
    brushAction->setCheckable(true);
    toolBar->addAction(brushAction);
    group->addAction(brushAction);
    QAction *eraserAction = new QAction(tr("Eraser"), toolBar);
    eraserAction->setIcon(QIcon(":/eraser.png"));
    eraserAction->setToolTip(tr("Eraser"));
    eraserAction->setStatusTip(tr("Eraser"));
    eraserAction->setCheckable(true);
    toolBar->addAction(eraserAction);
    group->addAction(eraserAction);
    QAction *startingAction = new QAction(tr("Starting"), toolBar);
    startingAction->setIcon(QIcon(":/starting.png"));
    startingAction->setToolTip(tr("Starting"));
    startingAction->setStatusTip(tr("Starting"));
    startingAction->setCheckable(true);
    toolBar->addAction(startingAction);
    group->addAction(startingAction);
    QAction *terminalAction = new QAction(tr("Terminal"), toolBar);
    terminalAction->setIcon(QIcon(":/terminal.png"));
    terminalAction->setToolTip(tr("Terminal"));
    terminalAction->setStatusTip(tr("Terminal"));
    terminalAction->setCheckable(true);
    toolBar->addAction(terminalAction);
    group->addAction(terminalAction);
    QToolBar *propertyBar = this->addToolBar("Property");
    QLabel *widthLabel = new QLabel(tr("Width: "));
    widthEdit = new QLineEdit(tr("600"));
    widthEdit->setFixedWidth(32);
    widthEdit->setValidator(new QIntValidator(1, 9999));
    QLabel *heightLabel = new QLabel(tr("Height: "));
    heightEdit = new QLineEdit(tr("500"));
    heightEdit->setFixedWidth(32);
    heightEdit->setValidator(new QIntValidator(1, 9999));
    showPathCheck = new QCheckBox(tr("Show path"));
    propertyBar->addWidget(widthLabel);
    propertyBar->addWidget(widthEdit);
    propertyBar->addWidget(heightLabel);
    propertyBar->addWidget(heightEdit);
    propertyBar->addWidget(showPathCheck);
    QToolBar *generateBar = this->addToolBar("Generate");
    QAction *generateAction = new QAction(tr("Generate"), generateBar);
    generateAction->setToolTip(tr("Generate"));
    generateAction->setStatusTip(tr("Generate"));
    QAction *clearAction = new QAction(tr("Clear"), generateBar);
    clearAction->setToolTip(tr("Clear"));
    clearAction->setStatusTip(tr("Clear"));
    QLabel *distanceLabel = new QLabel(tr("Distance"));
    distanceSlider = new QSlider();
    distanceSlider->setMinimum(2);
    distanceSlider->setMaximum(20);
    distanceSlider->setTickInterval(1);
    distanceSlider->setFixedWidth(60);
    distanceSlider->setOrientation(Qt::Horizontal);
    QLabel *errorLabel = new QLabel(tr("Error"));
    errorSlider = new QSlider();
    errorSlider->setMinimum(0);
    errorSlider->setMaximum(20);
    errorSlider->setTickInterval(1);
    errorSlider->setFixedWidth(60);
    errorSlider->setOrientation(Qt::Horizontal);
    generateBar->addWidget(distanceLabel);
    generateBar->addWidget(distanceSlider);
    generateBar->addWidget(errorLabel);
    generateBar->addWidget(errorSlider);
    generateBar->addAction(generateAction);
    generateBar->addAction(clearAction);
    QLabel *statusMsg = new QLabel;
    statusBar()->addWidget(statusMsg);
    mazeWidget = new MazeWidget();
    connect(clearAction, SIGNAL(triggered(bool)), mazeWidget, SLOT(clear()));
    connect(showPathCheck, SIGNAL(toggled(bool)), mazeWidget, SLOT(setPathVisibility(bool)));
    connect(arrowAction, SIGNAL(triggered(bool)), SLOT(arrowActionTriggered()));
    connect(brushAction, SIGNAL(triggered(bool)), SLOT(brushActionTriggered()));
    connect(eraserAction, SIGNAL(triggered(bool)), SLOT(eraserActionTriggered()));
    connect(startingAction, SIGNAL(triggered(bool)), SLOT(startingActionTriggered()));
    connect(terminalAction, SIGNAL(triggered(bool)), SLOT(terminalActionTriggered()));
    connect(heightEdit, SIGNAL(textChanged(QString)), SLOT(resizeActionTriggered()));
    connect(widthEdit, SIGNAL(textChanged(QString)), SLOT(resizeActionTriggered()));
    connect(generateAction, SIGNAL(triggered(bool)), SLOT(generateActionTriggered()));
    connect(saveAction, SIGNAL(triggered(bool)), SLOT(saveActionTriggered()));
    connect(aboutAction, SIGNAL(triggered(bool)), SLOT(aboutActionTriggered()));
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(mazeWidget);
    view = new MyView(scene);
    view->setBackgroundRole(QPalette::Dark);
    this->setCentralWidget(view);
    connect(this, SIGNAL(changeDrawStatus(MazeWidget::DrawStatus)),
            mazeWidget, SLOT(setDrawStatus(MazeWidget::DrawStatus)));
    mazeWidget->resize(600, 500);
    resize(800, 600);
}

void MainWindow::arrowActionTriggered()
{
    emit changeDrawStatus(MazeWidget::ARROW);
}

void MainWindow::brushActionTriggered()
{
    emit changeDrawStatus(MazeWidget::BRUSH);
}

void MainWindow::eraserActionTriggered()
{
    emit changeDrawStatus(MazeWidget::ERASER);
}

void MainWindow::startingActionTriggered()
{
    emit changeDrawStatus(MazeWidget::STARTING);
}

void MainWindow::terminalActionTriggered()
{
    emit changeDrawStatus(MazeWidget::TERMINAL);
}

void MainWindow::resizeActionTriggered()
{
    mazeWidget->resize(widthEdit->text().toInt(), heightEdit->text().toInt());
}

void MainWindow::generateActionTriggered()
{
    mazeWidget->generate(distanceSlider->value(), errorSlider->value());
}

void MainWindow::saveActionTriggered()
{
    mazeWidget->save();
}

void MainWindow::aboutActionTriggered()
{
    QMessageBox::about(this, tr("Maze Generator"), tr("Author: Hezhu"));
}


