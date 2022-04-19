/*
 * @Author: ImGili
 * @Description: 
 */
#include "Function/Render/RenderImplement/OpenGL/OpenGLRenderAPI.h"
#include<glad/glad.h>
namespace Soarscape
{
    void OpenGLRenderAPI::Init()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
