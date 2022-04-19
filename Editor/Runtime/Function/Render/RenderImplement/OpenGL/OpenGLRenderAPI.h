#pragma once
#include "Function/Render/RenderAPI.h"
namespace Soarscape
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void Init() override;
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
    };
}