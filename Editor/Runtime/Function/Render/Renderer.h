#pragma once
#include "Core/Base/PublicSingleton.h"
#include <osgQOpenGL/osgQOpenGLWidget>

namespace Soarscape
{
	class Renderer : public PublicSingleton<Renderer>
	{
	public:
		Renderer() = delete;
	private:
		osgQOpenGLWidget m_osgQt;
	};
}