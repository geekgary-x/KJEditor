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
		: QOpenGLWidget(parent)
	{}
	EditorRendererWidget::~EditorRendererWidget()
	{}

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
        event->button();
        PublicSingleton<EventSystem>::getInstance().sendEvent("EditorCamera_Process_Key", (void*)10);
    }

    void EditorRendererWidget::mouseReleaseEvent(QMouseEvent* event)
    {
    }

    void EditorRendererWidget::mouseDoubleClickEvent(QMouseEvent* event)
    {
    }

    void EditorRendererWidget::mouseMoveEvent(QMouseEvent* event)
    {
    }
    
}