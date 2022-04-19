#include "EditorUI.h"
#include <Core/Base/macro.h>
#include <Function/Render/Renderer.h>
namespace Soarscape
{
	EditorUI::EditorUI()
	{
		
	}
	void EditorUI::getFramebuffer()
	{

	}

	void EditorUI::setFramebuffer(std::shared_ptr<FrameBuffer>& framebuffer)
	{
		m_FrameBuffer = framebuffer;
	}

	void EditorUI::run()
	{
		LOG_INFO("EditorUI run");
		m_Mainwindow = new MainWindow;
		m_Mainwindow->showMaximized();
	}
}