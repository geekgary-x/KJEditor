#include "EditorRenderWidget.h"

#include <iostream>
#include <Core/Base/macro.h>
#include <Engine.h>
#include <Function/Render/Interface/Renderer.h>
#include <Function/Event/EventSystem.h>

#include <qelapsedtimer.h>
#include <qevent.h>
namespace Soarscape
{
	EditorRendererWidget::EditorRendererWidget(QWidget* parent)
		: QOpenGLWidget(parent), m_MousePos(std::make_shared<MousePos>(0.0f, 0.0f))
	{}
	EditorRendererWidget::~EditorRendererWidget()
	{
    }

	void EditorRendererWidget::initializeGL()
	{
        PublicSingleton<Engine>::getInstance().renderInitialize();
        PublicSingleton<Engine>::getInstance().logicalInitialize();
	}

	void EditorRendererWidget::resizeGL(int w, int h)
	{
        PublicSingleton<Renderer>::getInstance().screenFrameBuffer()->resize(w, h);
	}

	void EditorRendererWidget::paintGL()
	{
        QElapsedTimer timer;
        timer.start();
        PublicSingleton<Engine>::getInstance().logicalTick();
        PublicSingleton<Engine>::getInstance().renderTick(defaultFramebufferObject());
        update();
        PublicSingleton<Engine>::getInstance().DeltaTime = timer.nsecsElapsed()* 0.000000001f;
	}


    void EditorRendererWidget::mousePressEvent(QMouseEvent* event)
    {
    }

    void EditorRendererWidget::mouseReleaseEvent(QMouseEvent* event)
    {
        
    }

    void EditorRendererWidget::mouseDoubleClickEvent(QMouseEvent* event)
    {
    }

    void EditorRendererWidget::mouseMoveEvent(QMouseEvent* event)
    {
        m_MousePos->x = event->pos().x();
        m_MousePos->y = event->pos().y();
        if ((event->buttons() & Qt::LeftButton))
        {
            PublicSingletonInstance(EventSystem).sendEvent("EditCamera_Rotate", (void*)m_MousePos.get());
        }
    }
    
}