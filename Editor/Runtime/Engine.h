#pragma once
#include "Core/Base/PublicSingleton.h"
#include <filesystem>
#include <qapplication.h>
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
        void shutdownEngine();

    public:
        std::unique_ptr<QApplication> m_QtApp;
    };
} // namespace Scaor
