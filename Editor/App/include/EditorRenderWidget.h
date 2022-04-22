#pragma once
#include <glad/glad.h>
#include <qopenglwidget.h>
#include <memory>
namespace Soarscape
{
	class FrameBuffer;
	class VertexArray;
	class Shader;
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
		std::shared_ptr<VertexArray>	m_QuadVAO;
		std::shared_ptr<Shader>			m_ScreenShader;
	};
}