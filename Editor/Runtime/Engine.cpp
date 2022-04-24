#include "Engine.h"
#include "Function/Render/Interface/Renderer.h"
#include "Core/Base/macro.h"
#include <thread>
#include <glad/glad.h>
namespace Soarscape
{
    void Engine::startEngine(int argc, char* argv[])
    {
        LOG_INFO("Start editor engine");
        m_isRunning = true;
    }
    void Engine::run()
    {
        m_UISurface->getFramebuffer()->bind();
        PublicSingleton<Renderer>::getInstance().tick();
        glClearColor(0.3, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void Engine::shutdownEngine()
    {
        LOG_INFO("Shutdown editor engine");

        // waiting for other thread to release
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        m_isRunning = false;
    }
} // namespace SoaScape
