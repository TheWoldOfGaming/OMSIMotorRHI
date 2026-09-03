#include <Platform/Win32Window.h>

namespace Engine
{
	Win32Window::Win32Window()
	{

	}

	Win32Window::~Win32Window()
	{
		Destroy();
	}

	bool Win32Window::Create(const WindowDesc& desc)
	{
		WNDCLASSEXW wc{};
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.lpszClassName = L"EngineClassWindow";

		RegisterClassExW(&wc);

		m_width = desc.width;
		m_height = desc.height;

		m_hwnd = CreateWindowExW(
			0,
			L"EngineClassWindow",
			desc.title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			desc.width, desc.height,
			nullptr, nullptr,
			GetModuleHandle(nullptr),
			this
		);

		if (!m_hwnd)
		{
			DWORD error = GetLastError();
			return false;
		}
			

		ShowWindow(m_hwnd, SW_SHOW);
		return true;
	}

	void Win32Window::Destroy()
	{
		if (m_hwnd)
		{
			DestroyWindow(m_hwnd);
			m_hwnd = nullptr;
		}
	}

	void Win32Window::PumpMessage()
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_shouldClose = true;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	bool Win32Window::ShouldClose() const
	{
		return m_shouldClose;
	}

	int Win32Window::GetWidth() const
	{
		return m_width;
	}

	int Win32Window::GetHeight() const
	{
		return m_height;
	}

	void* Win32Window::GetNativeHandle() const
	{
		return m_hwnd;
	}


	LRESULT CALLBACK Win32Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Win32Window* self = nullptr;

		if (msg == WM_NCCREATE)
		{
			CREATESTRUCTW* cs = reinterpret_cast<CREATESTRUCTW*>(lParam);
			self = static_cast<Win32Window*>(cs->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
			self->m_hwnd = hwnd;
		}
		else
		{
			self = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (self)
		{
			return self->HandleMessage(msg, wParam, lParam);
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	LRESULT Win32Window::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_SIZE:
			m_width = LOWORD(lParam);
			m_height = HIWORD(lParam);
			return 0;

		default:
			return DefWindowProc(m_hwnd, msg, wParam, lParam);
		}
	}
}