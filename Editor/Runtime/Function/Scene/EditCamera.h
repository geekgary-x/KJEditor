#pragma once
#include "Function/Scene/Camera.h"
#include "Function/Render/Interface/UniformBuffer.h"
#include "Function/Event/Listener.h"
#include "glm/glm.hpp"
namespace Soarscape
{
    class EditorCamera : public Camera, public Listener
    {
    public:
        EditorCamera();
        void bind(size_t index = 0);
        void handleEvent(Event* event) override;

		//View settings
		void setCameraPos(const glm::vec3& v);
		void setCameraFocus(const glm::vec3& v);
		void setCameraUpVec(const glm::vec3& v);

		//Projection settings
		void setAspectRatio(const float ar);
		void setViewAngle(const float a);
		void setNearClipDist(const float d);
		void setFarClipDist(const float d);

		//Get matrix data
		glm::mat4 getViewMat();
		float* getViewMatRef();
		glm::mat4 getProjMat();
		float* getProjMatRef();
		// Get attitude
		glm::quat EditorCamera::getOrientation() const;
		glm::vec3 EditorCamera::getForwardDirection() const;
		glm::vec3 EditorCamera::getRightDirection() const;
		glm::vec3 EditorCamera::getUpDirection() const;
		glm::vec3 EditorCamera::calculatePosition();

		void EditorCamera::MouseZoom(float delta);
		float EditorCamera::ZoomSpeed() const;

		//Create matrices
		void genViewMat();
		void genProjMat();
    private:
		glm::vec2 m_InitialMousePosition = { 0.0, 0.0 };

		//View matrix variables
		glm::vec3 m_Pos; ///< position of the camera
		glm::vec3 m_FocalPoint; ///< focal point of the camera
		glm::vec3 m_Up; ///< the up direction for the camera
		float m_Distance = 20.0;


		//Projection matrix variables
		float m_AspectRatio; ///< aspect ratio
		float m_Angle; ///< angle in radians
		float m_Near; ///< near clipping distance
		float m_Far; ///< far clipping distance

		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		//functional matrices
		glm::mat4 m_View; ///< View matrix for OpenGL
		glm::mat4 m_Proj; ///< Projection matrix for OpenGL

        glm::mat4 m_ProjViewMatrix = glm::mat4(1);
        std::shared_ptr<UniformBuffer> m_UniformBuffer;

		void rotate(glm::vec2 delta);
		void pan(glm::vec2 delta);

		bool m_Begin = false;
		void begin(Event* event);
		void end(Event* event);
    };
}