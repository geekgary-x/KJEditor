#pragma once
#include "Function/Render/Interface/RenderAPI.h"
namespace Soarscape
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void init() override;
        void setClearColor(const glm::vec4& color) override;
        void clear() override;
    };
}