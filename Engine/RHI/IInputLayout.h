#pragma once

namespace Engine
{
	class IInputLayout
	{
	public:
		IInputLayout() = default;
		virtual ~IInputLayout() = default;

		virtual bool Create(void* nativeDevice, void* shaderByteCode, size_t byteCodeSize) = 0;
		virtual void Destroy() = 0;

		virtual void* GetLayoutPointer() const = 0;
	};
}