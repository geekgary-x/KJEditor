#pragma once
#include "Function/Scene/Camera.h"
#include "Function/Render/Interface/UniformBuffer.h"
#include "glm/glm.hpp"
namespace Soarscape
{
    class EditorCamera : public Camera
    {
    public:
        EditorCamera();
        void bind(size_t index = 0);
    private:
        glm::mat4 m_ProjViewMatrix = glm::mat4(1);
        std::shared_ptr<UniformBuffer> m_UniformBuffer;
    };
}