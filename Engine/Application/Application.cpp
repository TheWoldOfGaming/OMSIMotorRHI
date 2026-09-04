#include <Application/Application.h>
#include <Core/Common.h>
#include <RHI/IRenderContext.h>

#include <Core/Logger.h>

namespace Engine
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	bool Application::Initialize()
	{
		Logger::Initialize("Logs.log");
		Logger::Info(LogCategory::General, "OMSIEngine Version 1.0");
		// Log start

		WindowDesc desc;
		desc.width = 1280;
		desc.height = 720;
		desc.title = L"OMSIEngine Version 1.0";

		m_window = std::unique_ptr<IWindow>( FactoryCreateWindow(desc) );

		if (!m_window)
		{
			Logger::Critical(LogCategory::General, "Failed to create window.");
			return false;
		}

		RenderDeviceDesc renderDesc;
		renderDesc.hwnd = m_window->GetNativeHandle();
		renderDesc.width = desc.width;
		renderDesc.height = desc.height;

		m_renderDevice = std::unique_ptr<IRenderDevice>(FactoryCreateRenderDevice(renderDesc));

		if (!m_renderDevice)
		{
			Logger::Critical(LogCategory::General, "Failed to create render device.");
			return false;
		}

		return true;
	}

	void Application::Run()
	{
		while (!m_window->ShouldClose())
		{
			m_window->PumpMessage();

			m_renderDevice->GetContext()->Clear(0.0f, 0.2f, 0.4f, 1.0f);
			m_renderDevice->GetContext()->Present();

		}
	}

	void Application::Shutdown()
	{
		if (m_renderDevice)
		{
			m_renderDevice.reset();
		}

		if (m_window)
		{
			m_window->Destroy();
			m_window.reset();
		}
		
		Logger::Info(LogCategory::General, "OMSIEngine shutdown complete.");
	}
}