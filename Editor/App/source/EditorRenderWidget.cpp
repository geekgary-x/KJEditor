#include "EditorRenderWidget.h"

#include <iostream>

#include <Core/Base/macro.h>
#include <Function/Render/Interface/FrameBuffer.h>
#include <EditorUI.h>
#include <Engine.h>
#include <Resource/Data/Implement/VCG/VCGMesh.h>

#include <Function/Render/Interface/VertexArray.h>
#include <Function/Render/Interface/Shader.h>
#include <Function/Render/Interface/Renderer.h>
#include <Function/Render/Interface/Texture.h>

#include <Function/Event/EventSystem.h>
namespace Soarscape
{
    VCGMesh* vcgmesh;
    std::shared_ptr<Texture2D> _texture;
	EditorRendererWidget::EditorRendererWidget(QWidget* parent)
		: QOpenGLWidget(parent)
	{}
	EditorRendererWidget::~EditorRendererWidget()
	{}

	void EditorRendererWidget::initializeGL()
	{
        PublicSingleton<Renderer>::getInstance().initialize();

        vcgmesh = new VCGMesh("D:/datas/ply/shan.ply");
        _texture = Texture2D::create("D:/datas/ply/tayv6_2K_Albedo.png");
	}

	void EditorRendererWidget::resizeGL(int w, int h)
	{
        PublicSingleton<Renderer>::getInstance().screenFrameBuffer()->resize(w, h);
	}

	void EditorRendererWidget::paintGL()
	{
        // engine run
        //PublicSingleton<Engine>::getInstance().run();
        PublicSingleton<Renderer>::getInstance().begin();
        PublicSingleton<ShaderPool>::getInstance().get("MeshShader")->bind();
        _texture->bind(0);
        PublicSingleton<Renderer>::getInstance().render(vcgmesh);
        
        PublicSingleton<Renderer>::getInstance().end(defaultFramebufferObject());
	}

    void EditorRendererWidget::mousePressEvent(QMouseEvent* event)
    {
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