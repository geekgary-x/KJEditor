#pragma once
#include <glad/glad.h>
#include <qopenglwidget.h>
namespace Soarscape
{
	class EditorRendererWidget : public QOpenGLWidget
	{
	public:
		EditorRendererWidget(QWidget* parent);
		~EditorRendererWidget();
		
		void initializeGL() override;
		void resizeGL(int w, int h) override;
		void paintGL() override;
	private:

	};
}