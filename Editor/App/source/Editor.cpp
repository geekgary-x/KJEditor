#include "Editor.h"
#include "EditorUI.h"
#include <Core/Base/macro.h>
#include <Engine.h>
namespace Soarscape
{
	void Editor::initialize(Engine* engine_runtime)
	{
		LOG_INFO("Initilaize Eidtor");
		m_RunTimeEngine = engine_runtime;
		m_RunTimeEngine->setupUISurface(&PublicSingleton<EditorUI>::getInstance());
	}
	bool Editor::run()
	{
		LOG_INFO("Runing");
		m_RunTimeEngine->run();
		return m_RunTimeEngine->m_QtApp->exec();
	}
}

