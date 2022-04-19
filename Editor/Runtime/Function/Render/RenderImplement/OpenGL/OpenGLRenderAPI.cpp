/*
 * @Author: ImGili
 * @Description: 
 */
#include "Function/Render/RenderImplement/OpenGL/OpenGLRenderAPI.h"
#include<glad/glad.h>
namespace Soarscape
{
    void OpenGLRenderAPI::init()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
