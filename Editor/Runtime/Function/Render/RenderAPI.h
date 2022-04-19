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
        static API getAPI();
        static std::unique_ptr<RenderAPI> create();
        virtual void clear() = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void init() = 0;
    private:
        static API s_API;
    };
}