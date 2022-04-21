#include "EditorRenderWidget.h"
#include <qopenglcontext.h>
#include <Core/Base/macro.h>
#include <Function/Render/FrameBuffer.h>
#include <EditorUI.h>
#include <iostream>
#include "mesh_vert.h"
#include "mesh_frag.h"
#include "screenquad_vert.h"
#include "screenquad_frag.h"
#include "Engine.h"
namespace Soarscape
{
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

        GLuint quadVBO;
        // screen quad VAO
        glGenVertexArrays(1, &m_QuadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(m_QuadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        m_ScreenShader = glCreateProgram();
        GLuint sfrag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderBinary(1, &sfrag, GL_SHADER_BINARY_FORMAT_SPIR_V, screenquad_frag, sizeof(screenquad_frag));
        glSpecializeShader(sfrag, "main", 0, nullptr, nullptr);
        glAttachShader(m_ScreenShader, sfrag);

        GLuint svert = glCreateShader(GL_VERTEX_SHADER);
        glShaderBinary(1, &svert, GL_SHADER_BINARY_FORMAT_SPIR_V, screenquad_vert, sizeof(screenquad_vert));
        glSpecializeShader(svert, "main", 0, nullptr, nullptr);
        glAttachShader(m_ScreenShader, svert);
        glLinkProgram(m_ScreenShader);
        int success = 0;
        char infoLog[512] = { 0 };
        glGetProgramiv(m_ScreenShader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_ScreenShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGROG::COMPILATION_FAILED\n"
                << infoLog << std::endl;
        }
	}

	void EditorRendererWidget::resizeGL(int w, int h)
	{
        m_FrameBuffer->resize(w, h);
	}

	void EditorRendererWidget::paintGL()
	{
        // engine run
        PublicSingleton<Engine>::getInstance().run();
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject()); // ·µ»ØÄ¬ÈÏ
        glUseProgram(m_ScreenShader);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_QuadVAO);
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, m_FrameBuffer->getColorAttachmentRendererID());
        glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}