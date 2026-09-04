#pragma once

namespace Engine
{
	class IRenderContext;

	class IRenderDevice
	{
	public:
		virtual ~IRenderDevice() = default;

		virtual bool Initialize(void* hwnd, int width, int height) = 0;
		virtual void Shutdown() = 0;

		virtual IRenderContext* GetContext() = 0;

		virtual void Resize(int width, int height) = 0;
	};
}