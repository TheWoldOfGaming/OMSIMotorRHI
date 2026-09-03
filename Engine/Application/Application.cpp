#include <Application/Application.h>
#include <Core/Common.h>

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
		// Log start

		WindowDesc desc;
		desc.width = 1280;
		desc.height = 720;
		desc.title = L"OMSIEngine Version 1.0";

		m_window = std::unique_ptr<IWindow>( FactoryCreateWindow(desc) );

		if (!m_window)
		{
			//LOG_ERROR
			return false;
		}
		return true;
	}

	void Application::Run()
	{
		while (!m_window->ShouldClose())
		{
			m_window->PumpMessage();
		}
	}

	void Application::Shutdown()
	{
		if (m_window)
		{
			m_window->Destroy();
			m_window.reset();
		}
	}
}