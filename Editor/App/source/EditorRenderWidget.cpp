#include "EditorRenderWidget.h"
#include <qopenglcontext.h>
namespace Soarscape
{
	EditorRendererWidget::EditorRendererWidget(QWidget* parent)
		: QOpenGLWidget(parent)
	{}
	EditorRendererWidget::~EditorRendererWidget()
	{}

	void EditorRendererWidget::initializeGL()
	{
		initializeOpenGLFunctions();
		glClearColor(0.7f, .3f, 0.3f, 1.0f);
	}

	void EditorRendererWidget::resizeGL(int w, int h)
	{
	}

	void EditorRendererWidget::paintGL()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
}