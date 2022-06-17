#pragma once
#include <string>
#include<Windows.h>
#include<memory>
#include"Graphics.h"
#include"Mouse.h"
#include"keyBoard.h"
class Window
{
public:
	Window(int width, int height, std::wstring windowtitle)noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void InitWindow()noexcept;
	void RegisterWndClass()noexcept;
	void CreateHwnd()noexcept;
	HWND GetHWND()noexcept;
	void SetWindowTitle(std::wstring title)noexcept;
	LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	Graphics& Gfx();
	float GetAspect()const noexcept;
private:
	int m_iWidth;
	int m_iHeight;
	HINSTANCE m_hInst;
	HWND m_hWnd;
	std::wstring m_sWindowTitle;
	std::unique_ptr<Graphics> m_pGfx;

public:
	std::unique_ptr<DirectX::Mouse> m_pMouse;						// ЪѓБъ
	std::unique_ptr<DirectX::Keyboard> m_pKeyboard;					// МќХЬ
};

