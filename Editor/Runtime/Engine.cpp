#include "Engine.h"
#include "Core/Base/macro.h"
#include <thread>
namespace Soarscape
{
    void Engine::startEngine(int argc, char* argv[])
    {
        m_QtApp = std::make_unique<QApplication>(argc, argv);
        LOG_INFO("Start editor engine");
    }
    void Engine::run()
    {
        m_UISurface->run();
    }
    void Engine::shutdownEngine()
    {
        LOG_INFO("Shutdown editor engine");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
} // namespace SoaScape
