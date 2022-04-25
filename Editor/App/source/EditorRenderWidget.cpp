#include "EditorRenderWidget.h"

#include <iostream>
#include <Core/Base/macro.h>
#include <Engine.h>
#include <Function/Render/Interface/Renderer.h>
#include <Function/Event/EventSystem.h>
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
        PublicSingleton<Engine>::getInstance().logicalTick();
        PublicSingleton<Engine>::getInstance().renderTick(defaultFramebufferObject());
	}

    void EditorRendererWidget::mousePressEvent(QMouseEvent* event)
    {
        PublicSingleton<EventSystem>::getInstance().sendEvent("EditorCamera_Process_Key", (void*)10);
        PublicSingleton<EventSystem>::getInstance().processEvents();
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