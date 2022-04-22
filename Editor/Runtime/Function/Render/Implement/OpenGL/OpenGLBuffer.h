#pragma once
#include "Function/Render/Interface/Buffer.h"
namespace Soarscape
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const void* data, uint32_t size);
        OpenGLVertexBuffer(uint32_t size);
        virtual ~OpenGLVertexBuffer();
        void bind() override;
        void unbind() override;

        void setLayout(const BufferLayout& bufferLayout) override;
        const BufferLayout& getLayout() const override;

        void setData(const void* data, uint32_t size) override;
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer() = default;
        OpenGLIndexBuffer(const uint32_t* indics, uint32_t count);
        ~OpenGLIndexBuffer() = default;
        void bind() override;
        void unbind() override;
        uint32_t getCount() override;
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}