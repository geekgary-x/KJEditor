#include "EditorUI.h"
#include <Core/Base/macro.h>
namespace Soarscape
{
	EditorUI::EditorUI()
	{
		
	}
	const std::shared_ptr<FrameBuffer> EditorUI::getFramebuffer() const
	{
		return m_FrameBuffer;
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