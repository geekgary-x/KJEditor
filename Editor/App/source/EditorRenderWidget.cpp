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
namespace Soarscape
{
    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    unsigned int framebuffer;
    unsigned int texColorBuffer;
    unsigned int quadVAO, quadVBO;
    GLuint screenshader;
    GLuint program;

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
        float quadVertices[] = {// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                                // positions   // texCoords
                                -1.0f, 1.0f, 0.0f, 1.0f,
                                -1.0f, -1.0f, 0.0f, 0.0f,
                                1.0f, -1.0f, 1.0f, 0.0f,

                                -1.0f, 1.0f, 0.0f, 1.0f,
                                1.0f, -1.0f, 1.0f, 0.0f,
                                1.0f, 1.0f, 1.0f, 1.0f };

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

        // screen quad VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        program = glCreateProgram();
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

        screenshader = glCreateProgram();
        GLuint sfrag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderBinary(1, &sfrag, GL_SHADER_BINARY_FORMAT_SPIR_V, screenquad_frag, sizeof(screenquad_frag));
        glSpecializeShader(sfrag, "main", 0, nullptr, nullptr);
        glAttachShader(screenshader, sfrag);

        GLuint svert = glCreateShader(GL_VERTEX_SHADER);
        glShaderBinary(1, &svert, GL_SHADER_BINARY_FORMAT_SPIR_V, screenquad_vert, sizeof(screenquad_vert));
        glSpecializeShader(svert, "main", 0, nullptr, nullptr);
        glAttachShader(screenshader, svert);
        glLinkProgram(screenshader);
        glGetProgramiv(screenshader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(screenshader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGROG::COMPILATION_FAILED\n"
                << infoLog << std::endl;
        }

        // 帧缓冲创建
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        // 帧缓冲纹理创建
        glGenTextures(1, &texColorBuffer);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        // 将它附加到当前绑定的帧缓冲对象
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

        // 创建渲染缓冲对象
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void EditorRendererWidget::resizeGL(int w, int h)
	{
	}

	void EditorRendererWidget::paintGL()
	{
        glUseProgram(program);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_QuadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // 返回默认
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject()); // 返回默认
        glUseProgram(screenshader);
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(quadVAO);
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}