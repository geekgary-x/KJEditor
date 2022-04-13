#pragma once
#include "Core/Base/PublicSingleton.h"
#include <osgQOpenGL/osgQOpenGLWidget>

namespace Soarscape
{
	class Renderer : public PublicSingleton<Renderer>
	{
	public:
		Renderer() = default;
	public:
		osgQOpenGLWidget m_osgQt;
	};
}