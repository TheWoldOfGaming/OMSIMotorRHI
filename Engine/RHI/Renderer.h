#pragma once

#include <memory>

#include <Core/Common.h>
#include <RHI/IRenderDevice.h>

namespace Engine
{
    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer();

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        bool Initialize(
            void* hwnd,
            const WindowDesc& windowDesc
        );

		bool Resize(int width, int height);

        bool RenderFrame();

        void Shutdown();

    private:
        std::unique_ptr<IRenderDevice> m_renderDevice;
        bool m_initialized = false;
    };
}
