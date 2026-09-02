#pragma once
#include <Core/Common.h>

namespace Engine
{
	class IWindow
	{
	public:
		virtual ~IWindow() = default;

		virtual bool Create(const WindowDesc& desc) = 0;
		virtual void Destroy() = 0;

		virtual void PumpMessage() = 0;
		virtual bool ShouldClose() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void* GetNativeHandle() const = 0;
	};
}