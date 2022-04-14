#include "EditorUI.h"
#include <Core/Base/macro.h>
#include <Function/Render/Renderer.h>
namespace Soarscape
{
	void EditorUI::run()
	{
		LOG_INFO("EditorUI run");
		PublicSingleton<Renderer>::getInstance().m_osgQt.show();
	}
}