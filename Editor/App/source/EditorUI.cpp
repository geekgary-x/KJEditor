#include "EditorUI.h"
#include <Core/Base/macro.h>
#include <Function/Render/Renderer.h>
namespace Soarscape
{
	EditorUI::EditorUI()
	{

	}
	void EditorUI::run()
	{
		LOG_INFO("EditorUI run");
		m_Mainwindow.showMaximized();
	}
}