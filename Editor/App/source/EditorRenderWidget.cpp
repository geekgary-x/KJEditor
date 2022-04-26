#include "EditorRenderWidget.h"

#include <iostream>
#include <Core/Base/macro.h>
#include <Engine.h>
#include <Function/Render/Interface/Renderer.h>
#include <Function/Event/EventSystem.h>
#include <Function/Event/Input.h>

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
        MouseKey key;
        switch (event->button())
        {
        case Qt::LeftButton:
            key = MouseKey::Left;
            break;
        case Qt::MiddleButton:
            key = MouseKey::Middle;
            break;
        case Qt::RightButton:
            key = MouseKey::Right;
            break;
        default:
            break;
        }
        MouseInput* mouseInput = new MouseInput(key);
        PublicSingleton<EventSystem>::getInstance().sendEvent("EditorCamera_Process_Key", (void*)mouseInput);
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