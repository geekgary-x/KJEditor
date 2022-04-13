#include "Editor.h"
#include <Core/Base/macro.h>
#include <Engine.h>
#include <Function/Render/Renderer.h>
namespace Soarscape
{
	void Editor::initialize(Engine* engine_runtime)
	{
		LOG_INFO("Initilaize Eidtor");
		m_RunTimeEngine = engine_runtime;
	}
	bool Editor::run()
	{
		LOG_INFO("Runing");
		PublicSingleton<Renderer>::getInstance().m_osgQt.show();
		return m_RunTimeEngine->m_QtApp->exec();
	}
}

