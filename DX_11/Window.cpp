#include "Window.h"
namespace 
{
	Window* g_window = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_window->WndProc(hwnd, msg, wParam, lParam);
}


Window::Window(int width, int height, std::wstring windowtitle) noexcept:
	m_iWidth(width),
	m_iHeight(height),
	m_sWindowTitle(windowtitle),
	m_hInst(GetModuleHandle(nullptr)),
	m_hWnd(nullptr),
	m_pGfx(nullptr),
	m_pMouse(nullptr),
	m_pKeyboard(nullptr)
{
	g_window = this;
}

Window::~Window()
{
	DestroyWindow(m_hWnd);
}

void Window::InitWindow() noexcept
{
	RegisterWndClass();
	CreateHwnd();
	m_pGfx = std::make_unique<Graphics>(m_hWnd, m_iWidth, m_iHeight);
	m_pMouse = std::make_unique<DirectX::Mouse>();
	m_pKeyboard = std::make_unique<DirectX::Keyboard>();

	// 初始化鼠标，键盘不需要
	m_pMouse->SetWindow(m_hWnd);
	m_pMouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);
}

void Window::RegisterWndClass() noexcept
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hInstance = m_hInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"D3DWndClassName";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return;
	}
}

void Window::CreateHwnd() noexcept
{
	RECT wr = { 0,0,m_iWidth,m_iHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);
	int width = wr.right - wr.left;
	int height = wr.bottom - wr.top;
	m_hWnd = CreateWindow(L"D3DWndClassName", m_sWindowTitle.c_str(), WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_hInst, 0);
	if (!m_hWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return;
	}
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

HWND Window::GetHWND() noexcept
{
	return m_hWnd;
}

void Window::SetWindowTitle(std::wstring title) noexcept
{
	SetWindowText(m_hWnd, title.c_str());
}

LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		return 0;

	case WM_SIZE:
		return 0;

	case WM_ENTERSIZEMOVE:
		return 0;

	case WM_EXITSIZEMOVE:

		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_INPUT:
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_XBUTTONDOWN:

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_XBUTTONUP:

	case WM_MOUSEWHEEL:
	case WM_MOUSEHOVER:
	case WM_MOUSEMOVE:
		m_pMouse->ProcessMessage(msg, wParam, lParam);
		return 0;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		m_pKeyboard->ProcessMessage(msg, wParam, lParam);
		return 0;

	case WM_ACTIVATEAPP:
		m_pMouse->ProcessMessage(msg, wParam, lParam);
		m_pKeyboard->ProcessMessage(msg, wParam, lParam);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

Graphics& Window::Gfx()
{
	return *m_pGfx;
}

float Window::GetAspect() const noexcept
{
	return static_cast<float>(m_iWidth) / m_iHeight;
}
