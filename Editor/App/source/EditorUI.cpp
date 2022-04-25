#include "EditorUI.h"
#include <Core/Base/macro.h>
namespace Soarscape
{
	EditorUI::EditorUI()
	{
		
	}

	void EditorUI::run()
	{
		LOG_INFO("EditorUI run");
		m_Mainwindow = new MainWindow;
		m_Mainwindow->showMaximized();
	}
}