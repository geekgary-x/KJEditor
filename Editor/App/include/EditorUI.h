#pragma once
#include "Core/Base/PublicSingleton.h"
#include "Function/UI/UIInterface.h"
#include "Mainwindow.h"
namespace Soarscape
{
	class EditorUI : public UIInterface, public PublicSingleton<EditorUI>
	{
	public:
		EditorUI();

		void run() override;
	private:
		MainWindow* m_Mainwindow;
	};
}