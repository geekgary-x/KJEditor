#pragma once

namespace Soarscape
{
    class UIInterface
    {
    public:
        virtual void run() {}
        virtual void getFramebuffer() = 0;
    };
}