#include "Function/Render/Interface/Renderer.h"
#include "Function/Scene/EditCamera.h"
#include <glad/glad.h>
namespace Soarscape
{
	Renderer::Renderer()
	{
		m_Camera = std::make_shared<EditorCamera>();
		API = RenderAPI::create();
	}
	void Renderer::tick()
	{
		m_Camera->bind(0);
	}
	void Renderer::render(const Mesh* mesh)
	{
		mesh->m_VAO->bind();
		API->drawElements(mesh->m_VAO);
	}
}