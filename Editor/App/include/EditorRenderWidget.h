#pragma once
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
namespace Soarscape
{
	class EditorRendererWidget : public QOpenGLWidget, public QOpenGLFunctions
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