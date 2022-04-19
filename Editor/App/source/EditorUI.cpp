#include "EditorUI.h"
#include <Core/Base/macro.h>
#include <Function/Render/Renderer.h>
namespace Soarscape
{
	EditorUI::EditorUI()
	{
		FrameBufferSpecification spec;
		spec.AttachmentsSpecification = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::Depth };
		spec.Height = 1280;
		spec.Width = 720;
		/*m_FrameBuffer = FrameBuffer::create(spec);*/
	}
	void EditorUI::getFramebuffer()
	{

	}
	void EditorUI::run()
	{
		LOG_INFO("EditorUI run");
		m_Mainwindow = new MainWindow;
		m_Mainwindow->showMaximized();
	}
}