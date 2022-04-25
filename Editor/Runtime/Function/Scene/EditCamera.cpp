#include "Function/Scene/EditCamera.h"
#include "Core/Base/macro.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace Soarscape
{
	EditorCamera::EditorCamera()
	{
		glm::mat4 view = glm::translate(glm::mat4(1), { 0.0f, 0.0f, -10.0f });
		glm::mat4 proj = glm::perspective(10.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
		m_ProjViewMatrix =  proj * view;

		m_UniformBuffer = UniformBuffer::create(sizeof(m_ProjViewMatrix));
		m_UniformBuffer->setData(glm::value_ptr(m_ProjViewMatrix), sizeof(m_ProjViewMatrix));
	}
	void EditorCamera::bind(size_t index)
	{
		m_UniformBuffer->bind(index);
	}
	void EditorCamera::handleEvent(Event* event)
	{
		LOG_INFO("Get event message: {0}", (int)event->parameter())
	}
}