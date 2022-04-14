#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <QLabel>
#include <QTimer>
#include "Function/Render/Renderer.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	m_DockManager = new ads::CDockManager(this);

	ads::CDockWidget* DockWidget = new ads::CDockWidget("Viewport");
	DockWidget->setWidget(&Soarscape::PublicSingleton<Soarscape::Renderer>::getInstance().m_osgQt);

	m_DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

