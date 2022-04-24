#pragma once
#include "Function/Render/Interface/RenderAPI.h"
namespace Soarscape
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void init() override;
        void setClearColor(const glm::vec4& color) override;
        void drawElements(std::shared_ptr<VertexArray> vertexArray, uint32_t indexCount = 0) override;
        void clear() override;
    };
}