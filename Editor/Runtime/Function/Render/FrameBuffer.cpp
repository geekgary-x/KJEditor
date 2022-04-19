/*
 * @Author: ImGili
 * @Description: 
 */
#include "Function/Render/RenderAPI.h"
#include "Function/Render/FrameBuffer.h"
#include "Core/Base/macro.h"
#include "Function/Render/RenderImplement/OpenGL/OpenGLFrameBuffer.h"
namespace Soarscape
{
    std::shared_ptr<FrameBuffer> FrameBuffer::create(const FrameBufferSpecification& spec)
    {
        switch (RenderAPI::getAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "RenderAPI is None")
                break;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLFrameBuffer>(spec);
            break;
        default:
            break;
        }
        return nullptr;
    }
}
