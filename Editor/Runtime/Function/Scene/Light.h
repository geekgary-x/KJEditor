#pragma once
#include <glm/glm.hpp>
#include "Core/Base/PublicSingleton.h"
#include "Function/Render/Interface/UniformBuffer.h"
namespace Soarscape
{
    class GLobalLight : public PublicSingleton<GLobalLight>
    {
    public:
        struct  UniformBlock
        {
            glm::vec3 Position = { 0.0f, -10.0f, 0.0f };
            glm::vec3 AmbientColor = { 1.0f, 1.0f, 1.0f };
            glm::vec3 DiffuseColor = { 1.0f, 1.0f, 1.0f };
            glm::vec3 SpecularColor = { 1.0f, 1.0f, 1.0f };
        };
        GLobalLight();
        void bind(uint32_t index = 0);
        void updateBuffer();
        
    private:
        UniformBlock m_BlockData;
        std::shared_ptr<UniformBuffer> m_UniformBuffer;
    };
}