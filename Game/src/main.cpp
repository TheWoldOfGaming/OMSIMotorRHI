#include <Application/Application.h>


int main()
{
	Engine::Application app;
	if (!app.Initialize())
	{
		return -1;
	}

	app.Run();
	app.Shutdown();

	return 0;
}