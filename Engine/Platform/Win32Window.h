#pragma once
#include <Platform/IWindow.h>
#include <Windows.h>

namespace Engine
{
	class Win32Window : public IWindow
	{
	public:
		Win32Window();
		~Win32Window() override;

		bool Create(const WindowDesc& desc) override;
		void Destroy() override;

		void PumpMessage() override;
		bool ShouldClose() const override;

		int GetWidth() const override;
		int GetHeight() const override;

		void* GetNativeHandle() const override;

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

		HWND m_hwnd = nullptr;
		int m_width = 0;
		int m_height = 0;
		bool m_shouldClose = 0;
	};
}