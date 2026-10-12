#pragma once
#include <memory>

// Interfaces
#include <Platform/IWindow.h>

// Factories
#include <Platform/WindowFactory.h>

#include <RHI/Renderer.h>


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
		std::unique_ptr<Renderer> m_renderer;
	};
}