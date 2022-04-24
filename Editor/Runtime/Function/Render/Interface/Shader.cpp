#include "Function/Render/Interface/Shader.h"
#include "Function/Render/Interface/RenderAPI.h"
#include "Function/Render/Implement/OpenGL/OpenGLShader.h"
#include "Core/Base/macro.h"

#include "mesh_vert.h"
#include "mesh_frag.h"
#include "screenquad_vert.h"
#include "screenquad_frag.h"
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

    ShaderManager::ShaderManager()
    {
        addShader("MeshShader", mesh_vert, sizeof(mesh_vert), mesh_frag, sizeof(mesh_frag));
        addShader("ScreenShader", screenquad_vert, sizeof(screenquad_vert), screenquad_frag, sizeof(screenquad_frag));
    }

    void ShaderManager::addShader(const std::string& name, const uint32_t* vshader, size_t vsiz, const uint32_t* fshader, size_t fsize)
    {
        m_ShaderMap[name] = Shader::create(name);
        m_ShaderMap[name]->link(vshader, vsiz, fshader, fsize);
    }

    std::shared_ptr<Shader> ShaderManager::getShader(const std::string& name)
    {
        return m_ShaderMap[name];
    }

}
