
#include <RHI/Renderer.h>

#include <Core/Logger.h>
#include <RHI/IRenderContext.h>
#include <RHI/RenderDeviceFactory.h>

namespace Engine
{
    Renderer::~Renderer()
    {
        Shutdown();
    }

    bool Renderer::Initialize(
        void* hwnd,
        const WindowDesc& windowDesc
    )
    {
        if (m_initialized)
        {
            Logger::Warning(
                LogCategory::DX3D,
                "Renderer is already initialized."
            );

            return true;
        }

        if (!hwnd)
        {
            Logger::Error(
                LogCategory::DX3D,
                "Renderer initialization failed: invalid window handle."
            );

            return false;
        }

        if (windowDesc.width <= 0 || windowDesc.height <= 0)
        {
            Logger::Error(
                LogCategory::DX3D,
                "Renderer initialization failed: invalid window dimensions."
            );

            return false;
        }

        Logger::Info(
            LogCategory::DX3D,
            "Initializing renderer."
        );

        m_renderDevice = CreateRenderDevice();

        if (!m_renderDevice)
        {
            Logger::Critical(
                LogCategory::DX3D,
                "Failed to create render device."
            );

            return false;
        }

        RenderDeviceDesc deviceDesc{};
        deviceDesc.hwnd = hwnd;
        deviceDesc.width = windowDesc.width;
        deviceDesc.height = windowDesc.height;

        if (!m_renderDevice->Initialize(deviceDesc))
        {
            Logger::Critical(
                LogCategory::DX3D,
                "Failed to initialize render device."
            );

            m_renderDevice.reset();
            return false;
        }

        if (!m_renderDevice->GetContext())
        {
            Logger::Critical(
                LogCategory::DX3D,
                "Render device initialized without a render context."
            );

            m_renderDevice->Shutdown();
            m_renderDevice.reset();
            return false;
        }

        m_initialized = true;

        Logger::Info(
            LogCategory::DX3D,
            "Renderer initialized successfully."
        );

        return true;
    }

    bool Renderer::Resize(int width, int height)
    {
        if (!m_initialized || !m_renderDevice)
        {
            Logger::Error(
                LogCategory::DX3D,
                "Cannot resize renderer: render device is not initialized."
            );

            return false;
        }

        if (width <= 0 || height <= 0)
            return false;

        m_renderDevice->Resize(width, height);

        return true;
    }

    bool Renderer::RenderFrame()
    {
        if (!m_initialized || !m_renderDevice)
        {
            Logger::Error(
                LogCategory::DX3D,
                "Cannot render frame: renderer is not initialized."
            );

            return false;
        }

        IRenderContext* context = m_renderDevice->GetContext();

        if (!context)
        {
            Logger::Error(
                LogCategory::DX3D,
                "Cannot render frame: render context is unavailable."
            );

            return false;
        }

        // Begin frame and clear the back buffer.
        if (!context->BeginFrame(
            0.0f,
            0.2f,
            0.4f,
            1.0f))
        {
            Logger::Error(
                LogCategory::DX3D,
                "Failed to begin render frame."
            );

            return false;
        }

        // No draw calls yet. The current milestone is
        // displaying a stable background color.

        if (!context->Present())
        {
            Logger::Error(
                LogCategory::DX3D,
                "Failed to present rendered frame."
            );

            return false;
        }

        return true;
    }

    void Renderer::Shutdown()
    {
        if (!m_renderDevice && !m_initialized)
            return;

        Logger::Info(
            LogCategory::DX3D,
            "Renderer shutdown started."
        );

        if (m_renderDevice)
        {
            m_renderDevice->Shutdown();
            m_renderDevice.reset();
        }

        m_initialized = false;

        Logger::Info(
            LogCategory::DX3D,
            "Renderer shutdown completed."
        );
    }
}
