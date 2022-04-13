#pragma once
#include <Core/Base/PublicSingleton.h>
namespace Soarscape
{
	class Engine;
	class Editor : public PublicSingleton<Editor>
	{
	public:
		void initialize(Engine* engine_runtime);
		void run();

	private:
		Engine* m_RunTimeEngine;
	};
} // namespace Soarscape
