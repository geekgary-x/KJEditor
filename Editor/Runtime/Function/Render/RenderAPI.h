#pragma once
#include <memory>
#include <glm/glm.hpp>
namespace Soarscape
{
    class RenderAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL
        };
        static API GetAPI();
        static std::unique_ptr<RenderAPI> Create();
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Init() = 0;
    private:
        static API s_API;
    };
}