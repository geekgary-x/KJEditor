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
		ASSERT(gladLoadGL(), "glad loadGL failed!");
		glClearColor(0.3, 0.3, 0.3, 1.0);
		FrameBufferSpecification spec;
		spec.AttachmentsSpecification = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::Depth };
		spec.Height = 1280;
		spec.Width = 720;
		m_FrameBuffer = FrameBuffer::create(spec);
		PublicSingleton<EditorUI>::getInstance().setFramebuffer(m_FrameBuffer);
        
        float quadVertices[] = {// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                                // positions   // texCoords
                                -1.0f, 1.0f, 0.0f, 1.0f,
                                -1.0f, -1.0f, 0.0f, 0.0f,
                                1.0f, -1.0f, 1.0f, 0.0f,

                                -1.0f, 1.0f, 0.0f, 1.0f,
                                1.0f, -1.0f, 1.0f, 0.0f,
                                1.0f, 1.0f, 1.0f, 1.0f };
        m_QuadVAO = VertexArray::create();
        auto quadVBO = VertexBuffer::create((void*)quadVertices, sizeof(quadVertices));
        quadVBO->setLayout({
            { ShaderDataType::Float2, "aPos" },
            { ShaderDataType::Float2, "aTexCoord" }
            });
        m_QuadVAO->addVertexBuffer(quadVBO);

        vcgmesh = new VCGMesh("D:/datas/ply/shan.ply");
        _texture = Texture2D::create("D:/datas/ply/tayv6_2K_Albedo.png");
	}

	void EditorRendererWidget::resizeGL(int w, int h)
	{
        m_FrameBuffer->resize(w, h);
	}

	void EditorRendererWidget::paintGL()
	{
        // engine run
        PublicSingleton<Engine>::getInstance().run();
        PublicSingleton<ShaderPool>::getInstance().get("MeshShader")->bind();
        _texture->bind(0);
        PublicSingleton<Renderer>::getInstance().render(vcgmesh);
        
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject()); // ·µ»ØÄ¬ÈÏ
        PublicSingleton<ShaderPool>::getInstance().get("ScreenShader")->bind();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_QuadVAO->bind();
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, m_FrameBuffer->getColorAttachmentRendererID());
        glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}