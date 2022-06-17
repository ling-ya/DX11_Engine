#include"App.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE prevInstance,
	_In_ LPSTR cmdLine, 
	_In_ int showCmd)
{
	App* app = new App();
	app->Init();

	return app->Run();
}
