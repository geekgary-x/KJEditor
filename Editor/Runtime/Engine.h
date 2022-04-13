#pragma once
#include "Core/Base/PublicSingleton.h"
#include <filesystem>
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
        void startEngine(const EngineInitParams& param);
        void shutdownEngine();
    };
} // namespace Scaor
