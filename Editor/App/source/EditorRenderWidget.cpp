#include "EditorRenderWidget.h"
#include <qopenglcontext.h>
#include <Core/Base/macro.h>
#include <Function/Render/FrameBuffer.h>
#include <EditorUI.h>
#include <iostream>
#include "mesh_vert.h"
#include "mesh_frag.h"
namespace Soarscape
{
    
    const uint32_t aaavert = 0;
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
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f,  // right
            0.0f, 0.5f, 0.0f    // top
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
        m_QuadVAO = VAO;

        GLuint program = glCreateProgram();
        GLuint testfragid = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderBinary(1, &testfragid, GL_SHADER_BINARY_FORMAT_SPIR_V, mesh_frag, sizeof(mesh_frag));
        glSpecializeShader(testfragid, "main", 0, nullptr, nullptr);
        glAttachShader(program, testfragid);

        GLuint testvertid = glCreateShader(GL_VERTEX_SHADER);
        glShaderBinary(1, &testvertid, GL_SHADER_BINARY_FORMAT_SPIR_V, mesh_vert, sizeof(mesh_vert));
        glSpecializeShader(testvertid, "main", 0, nullptr, nullptr);
        glAttachShader(program, testvertid);
        glLinkProgram(program);
        int success = 0;
        char infoLog[512] = {0};
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGROG::COMPILATION_FAILED\n"
                << infoLog << std::endl;
        }
        glUseProgram(program);

	}

	void EditorRendererWidget::resizeGL(int w, int h)
	{
	}

	void EditorRendererWidget::paintGL()
	{
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_QuadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}