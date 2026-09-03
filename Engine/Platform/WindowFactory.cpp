#include <Platform/WindowFactory.h>
#include <Platform/Win32Window.h>

namespace Engine
{
	IWindow* FactoryCreateWindow(const WindowDesc& desc)
	{
#ifdef _WIN32
		Win32Window* window = new Win32Window();
		if (!window->Create(desc))
		{
			delete window;
			return nullptr;
		}
		return window;
#endif

		// LATER ALSO LINUX

	}
}