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

		virtual void mousePressEvent(QMouseEvent* event) override;
		virtual void mouseReleaseEvent(QMouseEvent* event) override;
		virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
		virtual void mouseMoveEvent(QMouseEvent* event) override;
	};
}