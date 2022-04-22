#include "EditorRenderWidget.h"

#include <iostream>

#include <Core/Base/macro.h>
#include <Function/Render/Interface//FrameBuffer.h>
#include <EditorUI.h>
#include <Engine.h>
#include <Resource/Data/Implement/VCG/VCGMesh.h>

#include <Function/Render/Interface/VertexArray.h>
#include <Function/Render/Interface/Shader.h>
// shader
#include "mesh_vert.h"
#include "mesh_frag.h"
#include "screenquad_vert.h"
#include "screenquad_frag.h"
namespace Soarscape
{
    std::shared_ptr<Shader> meshShader;
    VCGMesh* vcgmesh;
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

        vcgmesh = new VCGMesh("D:/datas/ply/triangle.ply");
        LOG_INFO("size of {0}", vcgmesh->m_V.size());
        
        m_ScreenShader = Shader::create("ScreenShader");
        m_ScreenShader->link(screenquad_vert, sizeof(screenquad_vert), screenquad_frag, sizeof(screenquad_frag));
        meshShader = Shader::create("MeshShader");
        meshShader->link(mesh_vert, sizeof(mesh_vert), mesh_frag, sizeof(mesh_frag));
	}

	void EditorRendererWidget::resizeGL(int w, int h)
	{
        m_FrameBuffer->resize(w, h);
	}

	void EditorRendererWidget::paintGL()
	{
        // engine run
        PublicSingleton<Engine>::getInstance().run();
        meshShader->bind();
        vcgmesh->m_VAO->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject()); // ����Ĭ��
        m_ScreenShader->bind();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_QuadVAO->bind();
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, m_FrameBuffer->getColorAttachmentRendererID());
        glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}