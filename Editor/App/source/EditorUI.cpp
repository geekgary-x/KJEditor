#include "EditorUI.h"
#include <Core/Base/macro.h>
namespace Soarscape
{
	EditorUI::EditorUI()
	{
		
	}

	EditorUI::~EditorUI()
	{
		delete m_Mainwindow;
	}

	void EditorUI::run()
	{
		LOG_INFO("EditorUI run");
		m_Mainwindow = new MainWindow;
		m_Mainwindow->showMaximized();
	}
}