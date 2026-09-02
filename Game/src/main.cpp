#include <Platform/Win32Window.h>


int main()
{
	Engine::Win32Window window;

	Engine::WindowDesc desc;
	desc.width = 1280;
	desc.height = 720;
	desc.title = L"Engine Test Window";

	if (!window.Create(desc))
	{
		return -1;
	}

	while (!window.ShouldClose())
	{
		window.PumpMessage();
	}

	window.Destroy();

	return 0;
}