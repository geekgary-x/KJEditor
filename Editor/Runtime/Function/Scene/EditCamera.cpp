#include "Function/Scene/EditCamera.h"
#include "Core/Base/macro.h"
#include "Function/Event/Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
namespace Soarscape
{
	EditorCamera::EditorCamera()
	{
		/*glm::mat4 view = glm::translate(glm::mat4(1), { 0.0f, 0.0f, -10.0f });
		glm::mat4 proj = glm::perspective(10.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
		m_ProjViewMatrix =  proj * view;*/

		

		m_AspectRatio = 4.0f / 3.0f;
#ifdef GLM_FORCE_RADIANS
		m_Angle = 0.785398f; //45 degrees
#else
		m_Angle = 45.0f; //45 degrees
#endif
		m_Near = 0.1f;
		m_Far = 100.0f;
		m_Pos = glm::vec3(10.0f, 10.0f, 8.0f);
		m_Up = { 0.0f, 1.0f, 0.0f };
		m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		m_AspectRatio = 800.0f / 600.0f;
		m_Angle = 10.0f;
		m_Near = 0.1f;
		m_Far = 1000.0f;
		genProjMat();
		genViewMat();
		m_ProjViewMatrix = m_Proj * m_View;
		m_UniformBuffer = UniformBuffer::create(sizeof(m_ProjViewMatrix));
		m_UniformBuffer->setData(glm::value_ptr(m_ProjViewMatrix), sizeof(m_ProjViewMatrix));
	}
	void EditorCamera::bind(size_t index)
	{
		m_UniformBuffer->bind(index);
	}
	void EditorCamera::handleEvent(Event* event)
	{
		/*static float tmp = 0;
		tmp += 0.2;
		glm::mat4 view = glm::translate(glm::mat4(1), { 0.0f, tmp, -10.0f });
		glm::mat4 proj = glm::perspective(10.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
		m_ProjViewMatrix = proj * view;

		m_UniformBuffer->setData(glm::value_ptr(m_ProjViewMatrix), sizeof(m_ProjViewMatrix));
		MouseInput* input = (MouseInput*)(event->parameter());
		if (input->key == MouseKey::Left)
		{
			LOG_INFO("left");
		}*/
		//LOG_INFO("Get event message: {0}", (uint32_t)input.key)
		m_Pos.x -= 0.5;
		genViewMat();
		m_ProjViewMatrix = m_Proj * m_View;
		m_UniformBuffer->setData(glm::value_ptr(m_ProjViewMatrix), sizeof(m_ProjViewMatrix));
	}

	void EditorCamera::setCameraPos(const glm::vec3& v)
	{
		m_Pos = v;
	}

	void EditorCamera::setCameraFocus(const glm::vec3& v)
	{
		m_FocalPoint = v;
	}

	void EditorCamera::setCameraUpVec(const glm::vec3& v)
	{
		m_Up = v;
	}

	void EditorCamera::setAspectRatio(const float ar)
	{
		m_AspectRatio = ar;
	}

	void EditorCamera::setViewAngle(const float a)
	{
		m_Angle = a;
	}

	void EditorCamera::setNearClipDist(const float d)
	{
		m_Near = d;
	}

	void EditorCamera::setFarClipDist(const float d)
	{
		m_Far = d;
	}

	glm::mat4 EditorCamera::getViewMat()
	{
		return m_View;
	}

	float* EditorCamera::getViewMatRef()
	{
		return glm::value_ptr(m_View);
	}

	glm::mat4 EditorCamera::getProjMat()
	{
		return m_Proj;
	}

	float* EditorCamera::getProjMatRef()
	{
		return glm::value_ptr(m_Proj);
	}

	void EditorCamera::genViewMat()
	{
		m_View = glm::lookAt(m_Pos, m_FocalPoint, m_Up);
	}

	void EditorCamera::genProjMat()
	{
		m_Proj = glm::perspective(m_Angle, m_AspectRatio, m_Near, m_Far);
	}
}