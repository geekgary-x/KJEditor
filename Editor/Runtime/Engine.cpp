#include "Engine.h"
#include "Core/Base/macro.h"
#include <thread>
namespace Soarscape
{
    void Engine::startEngine(const EngineInitParams& param)
    {
        LOG_INFO("Start editor engine");
    }
    void Engine::shutdownEngine()
    {
        LOG_INFO("Shutdown editor engine");
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
} // namespace SoaScape
