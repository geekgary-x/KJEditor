#pragma once
#include "Core/Base/PublicSingleton.h"
#include <filesystem>
#include <qapplication.h>
#include <Function/UI/UIInterface.h>
namespace Soarscape
{
    struct EngineInitParams
    {
        std::filesystem::path m_root_folder;
        std::filesystem::path m_config_file_path;
    };
    
    class Engine : public PublicSingleton<Engine>
    {
    public:
        void startEngine(int argc, char* argv[]);
        void setupUISurface(UIInterface* pui) { m_UISurface = pui; }
        void run();
        void shutdownEngine();

    public:
        std::unique_ptr<QApplication> m_QtApp;
        UIInterface* m_UISurface;
    };
} // namespace Scaor
