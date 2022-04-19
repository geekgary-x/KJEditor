#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <QLabel>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	m_DockManager = new ads::CDockManager(this);

	ads::CDockWidget* DockWidget = new ads::CDockWidget("Viewport");
	m_DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

