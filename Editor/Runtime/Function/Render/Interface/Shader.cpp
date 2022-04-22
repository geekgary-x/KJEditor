#include "Function/Render/Interface/Shader.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Function/Render/Implement/OpenGL/OpenGLShader.h"
#include "Core/Base/macro.h"
namespace Soarscape
{
    std::shared_ptr<Shader> Shader::create(const std::string& name)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            LOG_INFO("Create Shader: {0}", name);
            return std::make_shared<OpenGLShader>(name);
            break;
        default:
            break;
        }
        return nullptr;
    }

}
