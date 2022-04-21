#include "Function/Render/Renderer.h"

namespace Soarscape
{
	Renderer::Renderer()
	{

	}
	void Renderer::SetRendererTarget(std::shared_ptr<FrameBuffer>& framebuffer)
	{
		m_FrameBuffer = framebuffer;
	}
}