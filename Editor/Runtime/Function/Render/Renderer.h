#pragma once
#include "Core/Base/PublicSingleton.h"
#include "Function/Render/FrameBuffer.h"
namespace Soarscape
{
	class Renderer : public PublicSingleton<Renderer>
	{
	public:
		Renderer();
	public:
		std::shared_ptr<FrameBuffer> m_FrameBuffer;
	};
}