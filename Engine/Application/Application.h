#pragma once
#include <memory>
#include <Platform/IWindow.h>
#include <Platform/WindowFactory.h>

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
	};
}