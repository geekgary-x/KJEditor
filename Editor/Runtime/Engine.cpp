#include "Engine.h"

#include "Function/Render/Interface/Renderer.h"
#include "Function/Event/EventSystem.h"

#include "Function/Scene/EditCamera.h"
#include "Function/Scene/Scene.h"

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
        PublicSingleton<EventSystem>::getInstance().processEvents();
    }
    void Engine::shutdownEngine()
    {
        LOG_INFO("Shutdown editor engine");

        // Shut down event system
        PublicSingleton<EventSystem>::getInstance().unregisterAll(&PublicSingleton<EditorCamera>::getInstance());
        PublicSingleton<EventSystem>::getInstance().shutdown();

        // waiting for other thread to release
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        m_isRunning = false;
    }
    void Engine::renderRelatedInitialize()
    {
        //PublicSingleton<Renderer>::getInstance().initialize();
        PublicSingleton<Scene>::getInstance().initialize();
    }
} // namespace SoaScape
