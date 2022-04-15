#include "Engine.h"
#include "Core/Base/macro.h"
#include <thread>
namespace Soarscape
{
    void Engine::startEngine(const EngineInitParams& param)
    {
        LOG_INFO("Start editor engine");
        m_isRunning = true;
    }
    void Engine::run()
    {
        m_UISurface->run();
    }
    void Engine::shutdownEngine()
    {
        LOG_INFO("Shutdown editor engine");

        // waiting for other thread to release
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        m_isRunning = false;
    }
} // namespace SoaScape
