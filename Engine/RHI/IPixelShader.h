#pragma once
#include <string>

namespace Engine
{
	class IPixelShader
	{
	public:
		IPixelShader() = default;
		virtual ~IPixelShader() = default;

		virtual bool Create(void* nativeDevice, std::wstring shaderSourcePath, std::string entryPoint) = 0;
		virtual void Destroy() = 0;

		virtual void* GetShaderPointer() const = 0;
	};
}