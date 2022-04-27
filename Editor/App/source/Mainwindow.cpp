#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <QLabel>
#include <QTimer>
#include "EditorRenderWidget.h"
#include <iostream>
namespace Soarscape
{
    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        m_DockManager = new ads::CDockManager(this);

        m_ViewportDock = new ads::CDockWidget("Viewport");
        m_RendererWidget = new EditorRendererWidget(this);
        m_ViewportDock->setWidget(m_RendererWidget);
        m_DockManager->addDockWidget(ads::TopDockWidgetArea, m_ViewportDock);
    }

    MainWindow::~MainWindow()
    {
        delete ui;
        delete m_DockManager;
        //delete m_RendererWidget;
    }
}

