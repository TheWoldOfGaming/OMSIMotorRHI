#pragma once
#include <RHI/IVertexShader.h>

#include <wrl/client.h>
#include <d3d11.h>

namespace Engine
{
	class D3D11VertexShader : public IVertexShader
	{
	public:
		D3D11VertexShader() = default;
		~D3D11VertexShader() override;

		bool Create(void* nativeDevice, std::wstring shaderSourcePath, std::string entryPoint) override;
		void Destroy() override;
		void GetBytecode(void*& data, size_t& size) const override;
		void* GetShaderPointer() const override;

	private:
		Microsoft::WRL::ComPtr<ID3DBlob> m_byteCodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	};
}