#pragma once
#include "Function/Render/Interface/FrameBuffer.h"
namespace Soarscape
{
    class UIInterface
    {
    public:
        virtual void run() {}
        virtual const std::shared_ptr<FrameBuffer> getFramebuffer() const { return nullptr; }
    };
}