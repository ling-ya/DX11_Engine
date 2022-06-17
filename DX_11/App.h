#pragma once
#include"Window.h"
#include"Timer.h"
#include"Scene.h"
class App
{
public:
	App();
	~App() = default;
	void Init();
	int Run();
	void DrawScene();

private:
	void ShowFPS();
private:
	Window* mWin;
	Timer m_Timer;
	Scene* pScene;
};

