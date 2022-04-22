#pragma once
#include "Core/Base/PublicSingleton.h"
namespace Soarscape
{
	class Camera;
	class Renderer : public PublicSingleton<Renderer>
	{
	public:
		virtual void begin(const Camera&) {}

		virtual void tick() {}
	private:

	};
}