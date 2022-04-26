#include "Function/Scene/EditCamera.h"
#include "Core/Base/macro.h"
#include "Function/Event/Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

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
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_Begin", this);
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_Rotate", this);
		PublicSingleton<EventSystem>::getInstance().registerClient("EditCamera_End", this);

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

		if (event->eventId() == "EditCamera_Begin")
		{
			begin(event);
		}

		if (event->eventId() == "EditCamera_Rotate")
		{
			if (mousepos = static_cast<MousePos*>(event->parameter()))
			{
				const glm::vec2 mouse = { mousepos->x, mousepos->y };
				glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.001f;
				m_InitialMousePosition = mouse;
				rotate(delta);
				genViewMat();
				m_ProjViewMatrix = m_Proj * m_View;
				m_UniformBuffer->setData(glm::value_ptr(m_ProjViewMatrix), sizeof(m_ProjViewMatrix));
			}
		}

		if (event->eventId() == "EditCamera_End")
		{
			end(event);
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
		m_Pos = calculatePosition();

		glm::quat orientation = getOrientation();

		m_View = glm::translate(glm::mat4(1), m_Pos) * glm::toMat4(orientation);
		m_View = glm::inverse(m_View);
	}

	void EditorCamera::genProjMat()
	{
		m_Proj = glm::perspective(m_Angle, m_AspectRatio, m_Near, m_Far);
	}
	void EditorCamera::rotate(glm::vec2 delta)
	{
		float yawSign = getUpDirection().y > 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * 5.0f;
		m_Pitch += delta.y * 5.0f;
	}
	void EditorCamera::pan(glm::vec2 delta)
	{
		
	}

	void EditorCamera::begin(Event* event)
	{
		MousePos* mousepos = nullptr;
		if (!m_Begin)
		{
			if (mousepos = static_cast<MousePos*>(event->parameter()))
			{
				m_InitialMousePosition = { mousepos->x, mousepos->y };
			}
		}
		m_Begin = true;
	}

	void EditorCamera::end(Event* event)
	{
		m_Begin = false;
	}

	glm::quat EditorCamera::getOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	glm::vec3 EditorCamera::getForwardDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 EditorCamera::getRightDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(1.0, 0.0, 0.0));
	}

	glm::vec3 EditorCamera::getUpDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0, 1.0, 0.0));
	}
	glm::vec3 EditorCamera::calculatePosition()
	{
		return m_FocalPoint - getForwardDirection() * m_Distance;
	}

	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += getForwardDirection();
			m_Distance = 1.0f;
		}
	}

	float EditorCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

}