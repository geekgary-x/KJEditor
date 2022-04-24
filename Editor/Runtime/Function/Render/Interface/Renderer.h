#pragma once
#include "Core/Base/PublicSingleton.h"
#include "Function/Scene/Camera.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Resource/Data/Interface/Mesh.h"
namespace Soarscape
{
	class Renderer : public PublicSingleton<Renderer>
	{
	public:

		Renderer();

		virtual void tick();

		void setCamera(std::shared_ptr<Camera> cmera) { m_Camera; }
		void render(const Mesh* mesh);
		std::unique_ptr<RenderAPI> API;
	private:
		std::shared_ptr<Camera> m_Camera;
	};
}