#include <iostream>
#include <Engine.h>
#include <Editor.h>

int main(int argc, char *argv[])
{
    Soarscape::EngineInitParams param;
    Soarscape::PublicSingleton<Soarscape::Engine>::getInstance().startEngine(param);
    Soarscape::PublicSingleton<Soarscape::Editor>::getInstance().initialize(argc, argv);
    Soarscape::PublicSingleton<Soarscape::Editor>::getInstance().run();
    Soarscape::PublicSingleton<Soarscape::Engine>::getInstance().shutdownEngine();
}
