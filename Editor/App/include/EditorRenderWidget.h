#pragma once
#include <glad/glad.h>
#include <qopenglwidget.h>
namespace Soarscape
{
	class FrameBuffer;
	class EditorRendererWidget : public QOpenGLWidget
	{
	public:
		EditorRendererWidget(QWidget* parent);
		~EditorRendererWidget();
		
		void initializeGL() override;
		void resizeGL(int w, int h) override;
		void paintGL() override;
	private:
		std::shared_ptr<FrameBuffer>	m_FrameBuffer;
		uint32_t						m_QuadVAO;
		GLuint							m_ScreenShader;
	};
}