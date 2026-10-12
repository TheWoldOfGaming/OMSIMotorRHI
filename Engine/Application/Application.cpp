#include <Application/Application.h>
#include <Core/Common.h>
#include <RHI/IRenderContext.h>

#include <Core/Logger.h>

namespace Engine
{
	Application::Application()
	{
		Logger::Initialize("Logs.log");
		Logger::SetLogLevel(LogLevel::Info);
		Logger::Debug(LogCategory::General, "Application object constructed.");
	}

	Application::~Application()
	{
		Logger::Debug(LogCategory::General, "Application object destroyed.");
	}

	bool Application::Initialize()
	{
		Logger::Info(LogCategory::General, "Application initialization started.");

		// Init Window

		WindowDesc windowDesc;
		windowDesc.width = 1280;
		windowDesc.height = 720;
		windowDesc.title = L"OMSIEngine Version 1.0";

		Logger::Debug(LogCategory::General, "Creating application window.");

		m_window = std::unique_ptr<IWindow>( FactoryCreateWindow(windowDesc) );

		if (!m_window)
		{
			Logger::Critical(LogCategory::General, "Failed to create window.");
			return false;
		}

		Logger::Info(
			LogCategory::General,
			"Application window created successfully."
		);

		m_renderer = std::make_unique<Renderer>();
		if (!m_renderer->Initialize(m_window->GetNativeHandle(), windowDesc))
		{
			Logger::Critical(
				LogCategory::General,
				"Renderer initialization failed."
			);

			return false;
		}

		Logger::Info(
			LogCategory::General,
			"Application initialization completed successfully."
		);

		return true;
	}

	void Application::Run()
	{
		if (!m_window || !m_renderer)
		{
			Logger::Error(
				LogCategory::General,
				"Cannot run application: initialization is incomplete."
			);

			return;
		}

		Logger::Info(
			LogCategory::General,
			"Application main loop started."
		);

		int lastWidth = m_window->GetWidth();
		int lastHeight = m_window->GetHeight();

		while (!m_window->ShouldClose())
		{
			m_window->PumpMessage();

			if (m_window->ShouldClose())
				break;

			const int width = m_window->GetWidth();
			const int height = m_window->GetHeight();

			if (width <= 0 || height <= 0)
				continue;

			if (width != lastWidth || height != lastHeight)
			{
				Logger::Debug(
					LogCategory::DX3D,
					"Window size changed."
				);

				m_renderer->Resize(width, height);

				lastWidth = width;
				lastHeight = height;
			}

			m_renderer->RenderFrame();
		}
	}

	void Application::Shutdown()
	{
		if (m_renderer)
		{
			m_renderer.reset();
		}

		if (m_window)
		{
			m_window->Destroy();
			m_window.reset();
		}

		Logger::Info(
			LogCategory::General,
			"OMSIEngine shutdown complete."
		);
	}
}