#include "Function/Render/RenderAPI.h"
#include "Function/Render/RenderImplement/OpenGL/OpenGLRenderAPI.h"
#include "Core/Base/macro.h"

namespace Soarscape
{
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

    RenderAPI::API RenderAPI::GetAPI()
    {
        return s_API;
    }

    std::unique_ptr<RenderAPI> RenderAPI::Create()
    {
        switch (s_API)
        {
        case API::None:
            LOG_ERROR("RenderAPI is None");
            break;
        case API::OpenGL:
            return std::make_unique<OpenGLRenderAPI>();
            break;
        default:
            break;
        }
        LOG_ERROR("API is not defined!");
    }
}

