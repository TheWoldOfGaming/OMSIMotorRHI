#pragma once
#include <string>

namespace Engine
{
	class IVertexShader
	{
	public:
		IVertexShader() = default;
		virtual ~IVertexShader() = default;

		virtual bool Create(void* nativeDevice, std::wstring shaderSourcePath, std::string entryPoint) = 0;
		virtual void Destroy() = 0;

		virtual void GetBytecode(void*& data, size_t& size) const = 0;
		virtual void* GetShaderPointer() const = 0;
	};
}