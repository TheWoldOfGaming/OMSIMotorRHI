#include <Core/Logger.h>

#include <RHI/DX11/D3D11VertexShader.h>
#include <d3dcompiler.h>
#include <string>

namespace Engine
{
	bool D3D11VertexShader::Create(void* nativeDevice, std::wstring shaderSourcePath, std::string entryPoint)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

		HRESULT hr = D3DCompileFromFile(
			shaderSourcePath.c_str(),
			nullptr,
			nullptr,
			entryPoint.c_str(),
			"vs_5_0",
			0,
			0,
			&m_byteCodeBlob,
			&errorBlob
		);

		if (FAILED(hr))
		{
			if (errorBlob)
			{
				Logger::Error(LogCategory::DX3D, static_cast<const char*>(errorBlob->GetBufferPointer()));
			}
			else
			{
				Logger::Error(LogCategory::DX3D, "Failed to compile Vertex Shader bytecode.");
			}

			return false;
		}

		ID3D11Device* device = static_cast<ID3D11Device*>(nativeDevice);

		hr = device->CreateVertexShader(
			m_byteCodeBlob->GetBufferPointer(),
			m_byteCodeBlob->GetBufferSize(),
			nullptr,
			&m_vertexShader
		);

		if (FAILED(hr))
		{
			Logger::Error(LogCategory::DX3D, "Failed to create Vertex Shader from bytecode.");
			return false;
		}

		return true;
	}

	void D3D11VertexShader::Destroy()
	{
		m_byteCodeBlob.Reset();
		m_vertexShader.Reset();
	}

	void D3D11VertexShader::GetBytecode(void*& data, size_t& size) const
	{
		data = m_byteCodeBlob->GetBufferPointer();
		size = m_byteCodeBlob->GetBufferSize();
	}

	D3D11VertexShader::~D3D11VertexShader()
	{
		Destroy();
	}

	void* D3D11VertexShader::GetShaderPointer() const
	{
		return m_vertexShader.Get();
	}
}