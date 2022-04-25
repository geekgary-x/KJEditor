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
    private:
        glm::mat4 m_ProjViewMatrix = glm::mat4(1);
        std::shared_ptr<UniformBuffer> m_UniformBuffer;
    };
}