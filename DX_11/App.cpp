#include "App.h"
#include <sstream>
#include <iomanip>

App::App() :mWin(new Window(1280, 720, L"DX11_Engine")), pScene(nullptr)
{
	mWin->InitWindow();
}

void App::Init()
{
	pScene = new Scene();
	pScene->m_pWindow = mWin;
	pScene->Init();
}

int App::Run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			ShowFPS();
			pScene->UpdateScene(m_Timer.Mark());
			DrawScene();
		}
	}
	return (int)msg.wParam;
}

void App::DrawScene()
{
	float c = (float)sin(m_Timer.Peek()) / 2.0f + 0.5f;
	mWin->Gfx().ClearBuffer(0.1921f, 0.3019f, 0.4075f);
	//mWin->Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);
	pScene->UpdateReflectState();
	mWin->Gfx().OnRender(m_Timer.Mark());//»æÖÆ·´Éä

	//pScene->UpdateNormalState();
	//mWin->Gfx().OnRender(m_Timer.Mark());
	//mWin->Gfx().OnRender(m_Timer.Mark());
}

void App::ShowFPS()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;
	frameCnt++;
	if ((m_Timer.Peek() - timeElapsed) >=1.0f)
	{
		float fps = (float)frameCnt;
		std::wostringstream oss;
		oss.precision(6);
		oss << L"DX11Engine  " << L"FPS:" << std::setprecision(1) << std::fixed << fps;
		mWin->SetWindowTitle(oss.str().c_str());
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

