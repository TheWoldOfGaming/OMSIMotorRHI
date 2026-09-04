#pragma once
#include <memory>
#include <Platform/IWindow.h>
#include <Platform/WindowFactory.h>
#include <RHI/IRenderDevice.h>
#include <RHI/RenderDeviceFactory.h>

namespace Engine
{
	class Application
	{
	public:
		Application();
		~Application();

		bool Initialize();
		void Run();
		void Shutdown();

	private:
		std::unique_ptr<IWindow> m_window;
		std::unique_ptr<IRenderDevice> m_renderDevice;
	};
}