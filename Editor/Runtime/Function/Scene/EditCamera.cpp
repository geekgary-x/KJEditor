#include "Function/Scene/EditCamera.h"
#include "Core/Base/macro.h"
#include "Function/Event/Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Engine.h"
#include "Function/Event/EventSystem.h"
#include "Function/Event/Input.h"
#include "Core/Base/macro.h"
namespace Soarscape
{
	EditorCamera::EditorCamera()
	{
		// register Event
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_Rotate", this);

#ifdef GLM_FORCE_RADIANS
		m_Angle = 0.785398f; //45 degrees
#else
		m_Angle = 10.0f; //45 degrees
#endif
		m_Near = 0.1f;
		m_Far = 100.0f;
		m_Pos = glm::vec3(10.0f, 10.0f, 8.0f);
		m_Up = { 0.0f, 1.0f, 0.0f };
		m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		m_AspectRatio = 800.0f / 600.0f;
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
		MousePos* mousepos = nullptr;
		if (event->eventId() == "EditCamera_Rotate")
		{
			if (mousepos = static_cast<MousePos*>(event->parameter()))
			{
				LOG_INFO("Mouse pos: {0} {1}", mousepos->x, mousepos->y);
			}
			m_Pos.x -= 1000.0 * PublicSingleton<Engine>::getInstance().DeltaTime;
			genViewMat();
			m_ProjViewMatrix = m_Proj * m_View;
			m_UniformBuffer->setData(glm::value_ptr(m_ProjViewMatrix), sizeof(m_ProjViewMatrix));
		}
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