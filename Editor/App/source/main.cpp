#include <iostream>
#include <Engine.h>
int main(int argc, char *argv[])
{
    Soarscape::EngineInitParams param;
    Soarscape::PublicSingleton<Soarscape::Engine>::getInstance().startEngine(param);
}
//! [2]
