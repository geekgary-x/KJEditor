#pragma once
#include "Function/Render/Interface/UniformBuffer.h"
namespace Soarscape
{
	class Camera
	{
	public:
		Camera() = default;

		virtual ~Camera() = default;
		
		virtual void bind(size_t index = 0) = 0;
	protected:
	};
}