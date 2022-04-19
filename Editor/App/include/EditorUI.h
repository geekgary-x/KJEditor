#pragma once
#include "Core/Base/PublicSingleton.h"
#include "Function/UI/UIInterface.h"
#include "Mainwindow.h"
#include <Function/Render/FrameBuffer.h>
namespace Soarscape
{
	class EditorUI : public UIInterface, public PublicSingleton<EditorUI>
	{
	public:
		EditorUI();
		void getFramebuffer() override;
		void run() override;
	private:
		MainWindow* m_Mainwindow;
		std::shared_ptr<FrameBuffer> m_FrameBuffer;
	};
}